// Copyright (c) 2025 Boss
// Distributed under the MIT License.
// See LICENSE file in the project root for full license information.

#ifndef FASTIPC_SIMPLE_CHANNEL_H
#define FASTIPC_SIMPLE_CHANNEL_H

#include <cstddef>
#include <string>
#include <vector>

#include "fastipc/i_channel.h"

namespace fastipc {

// SimpleChanel is a basic implementation of IChannel that allows sending and
// receiving data in a straightforward manner. It uses an internal buffer to
// store data sent through the channel and allows retrieval of that data.
class SimpleChanel : public IChannel {
 public:
  explicit SimpleChanel(const std::string& name);
  ~SimpleChanel() override;

  SimpleChanel(const SimpleChanel&) = delete;
  SimpleChanel& operator=(const SimpleChanel&) = delete;

  // Send data through the channel
  bool Send(const void* data, size_t size) override;

  // Receive data from the channel
  size_t Receive(void* buffer, size_t sizes) override;

  // Return the name of the channel
  const std::string& Name() const override;

 private:
  // Name of the channel
  std::string name_;

  // Internal buffer to hold data sent through the channel
  // This buffer is used to store the data sent via Send() and is read by
  // Receive().
  std::vector<char> buffer_;
};

}  // namespace fastipc

#endif  // FASTIPC_SIMPLE_CHANNEL_H
