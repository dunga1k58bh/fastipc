// Copyright (c) 2025 Boss
// Distributed under the MIT License.
// See LICENSE file in the project root for full license information.

#include "core/simple_channel.h"

namespace fastipc {

SimpleChanel::SimpleChanel(const std::string& name) : name_(name) {}

SimpleChanel::~SimpleChanel() = default;

bool SimpleChanel::Send(const void* data, size_t size) {
  if (size == 0 || !data) {
    return false;
  }
  buffer_.resize(size);
  std::memcpy(buffer_.data(), data, size);
  return true;
}

size_t SimpleChanel::Receive(void* buffer, size_t sizes) {
  if (sizes == 0 || buffer_.empty()) {
    return 0;
  }
  size_t to_copy = std::min(sizes, buffer_.size());
  std::memcpy(buffer, buffer_.data(), to_copy);
  return to_copy;
}

const std::string& SimpleChanel::Name() const {
  return name_;
}

}  // namespace fastipc
