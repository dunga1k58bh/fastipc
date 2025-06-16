// Copyright (c) 2025 Boss
// Distributed under the MIT License.
// See LICENSE file in the project root for full license information.

#include "fastipc/shared_memory.h"

#include <stdexcept>

namespace {
static constexpr size_t kMaxSize = 65536;
}

namespace fastipc {

SharedMemory::SharedMemory(const std::string& name)
    : name_(name), mapping_handle_(nullptr), memory_ptr_(nullptr) {
  // Windows shared memory object name must be prefixed with "Local\\" or
  // "Global\\"
  std::string full_name = "Local\\" + name_;

  // Create or open a file mapping object (shared memory)
  mapping_handle_ = CreateFileMappingA(
      INVALID_HANDLE_VALUE,  // use system paging file
      nullptr,               // default security
      PAGE_READWRITE,        // read/write access
      0,                     // maximum object size (high-order DWORD)
      65536,                 // maximum object size (low-order DWORD) — 64 KB
      full_name.c_str());    // name of mapping object

  if (!mapping_handle_) {
    throw std::runtime_error("Failed to create shared memory: " + name_);
  }

  // Map a view of the file into the address space
  memory_ptr_ = MapViewOfFile(mapping_handle_,      // handle to map object
                              FILE_MAP_ALL_ACCESS,  // read/write permission
                              0, 0, 0);             // map entire file

  if (!memory_ptr_) {
    CloseHandle(mapping_handle_);
    throw std::runtime_error("Failed to map shared memory: " + name_);
  }
}

SharedMemory::~SharedMemory() {
  if (memory_ptr_) {
    UnmapViewOfFile(memory_ptr_);
    memory_ptr_ = nullptr;
  }
  if (mapping_handle_) {
    CloseHandle(mapping_handle_);
    mapping_handle_ = nullptr;
  }
}

bool SharedMemory::Send(const void* data, size_t size) {
  if (!memory_ptr_ || !data || size == 0 ||
      size + sizeof(uint32_t) > kMaxSize) {
    return false;
  }

  // Ghi độ dài (4 byte)
  uint32_t len = static_cast<uint32_t>(size);
  memcpy(memory_ptr_, &len, sizeof(len));

  // Ghi dữ liệu ngay sau độ dài
  memcpy(static_cast<uint8_t*>(memory_ptr_) + sizeof(len), data, size);
  return true;
}

size_t SharedMemory::Receive(void* buffer, size_t size) {
  if (!memory_ptr_ || !buffer || size == 0) {
    return 0;
  }

  uint32_t len = 0;
  memcpy(&len, memory_ptr_, sizeof(len));

  if (len == 0 || len > size || len + sizeof(len) > kMaxSize) {
    return 0;  // dữ liệu lỗi hoặc tràn buffer
  }

  memcpy(buffer, static_cast<uint8_t*>(memory_ptr_) + sizeof(len), len);
  return len;
}

const std::string& SharedMemory::Name() const {
  return name_;
}

}  // namespace fastipc
