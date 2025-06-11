// Copyright (c) 2025 Boss
// Distributed under the MIT License.
// See LICENSE file in the project root for full license information.

#ifndef FASTIPC_I_CHANNEL_H
#define FASTIPC_I_CHANNEL_H

#include <cstddef>
#include <string>

namespace fastipc {

class IChannel {
 public:
  virtual ~IChannel() = default;

  // Method to send data through the channel
  virtual bool Send(const void* data, size_t size) = 0;

  // Method to receive data from the channel
  virtual size_t Receive(void* buffer, size_t sizes) = 0;

  // Return the name of the channel
  virtual const std::string& Name() const = 0;
};

}  // namespace fastipc

#endif  // FASTIPC_I_CHANNEL_H
