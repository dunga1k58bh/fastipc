// Copyright (c) 2025 Boss
// Distributed under the MIT License.
// See LICENSE file in the project root for full license information.

#ifndef FASTIPC_SHARED_MEMORY_H
#define FASTIPC_SHARED_MEMORY_H

#include <windows.h>

#include <string>

#include "fastipc/i_channel.h"

namespace fastipc {

class SharedMemory : public IChannel {
 public:
  // Constructor: name is used to identify the shared memory segment
  explicit SharedMemory(const std::string& name);

  // Destructor
  ~SharedMemory() override;

  // Disable copy
  SharedMemory(const SharedMemory&) = delete;
  SharedMemory& operator=(const SharedMemory&) = delete;

  // IChannel interface
  bool Send(const void* data, size_t size) override;
  size_t Receive(void* buffer, size_t size) override;
  const std::string& Name() const override;

 private:
  std::string name_;
  HANDLE mapping_handle_;
  void* memory_ptr_;
  // Add internal handles or pointers for shared memory here
};

}  // namespace fastipc

#endif  // FASTIPC_SHARED_MEMORY_H
