// Copyright (c) 2025 Boss
// Distributed under the MIT License.
// See LICENSE file in the project root for full license information.

#include "core/simple_channel.h"

#include <gtest/gtest.h>

#include <cstring>

namespace fastipc {

TEST(SimpleChanelTest, NameReturnsCorrectValue) {
  SimpleChanel channel("TestChannel");
  EXPECT_EQ(channel.Name(), "TestChannel");
}

TEST(SimpleChanelTest, SendCopiesData) {
  SimpleChanel channel("Sender");
  const char* message = "Hello, FastIPC!";
  bool result = channel.Send(message, std::strlen(message) + 1);
  EXPECT_TRUE(result);
}

TEST(SimpleChanelTest, ReceiveCopiesDataBack) {
  SimpleChanel channel("Echo");

  const char* msg = "DataStream";
  channel.Send(msg, std::strlen(msg) + 1);

  char buffer[64] = {};
  size_t received = channel.Receive(buffer, sizeof(buffer));

  EXPECT_GT(received, 0);
  EXPECT_STREQ(buffer, msg);
}

TEST(SimpleChanelTest, SendFailsWithNullData) {
  SimpleChanel channel("InvalidSender");
  EXPECT_FALSE(channel.Send(nullptr, 10));
}

TEST(SimpleChanelTest, ReceiveReturnsZeroIfBufferIsEmpty) {
  SimpleChanel channel("EmptyBuffer");
  char buf[16];
  size_t received = channel.Receive(buf, sizeof(buf));
  EXPECT_EQ(received, 0);
}

TEST(SimpleChanelTest, ReceiveTruncatesIfBufferTooSmall) {
  SimpleChanel channel("TruncationTest");
  const char* msg = "LongMessage";
  channel.Send(msg, std::strlen(msg) + 1);

  char small_buf[5] = {};
  size_t received = channel.Receive(small_buf, sizeof(small_buf));

  EXPECT_EQ(received, sizeof(small_buf));
  // Note: cannot expect full message due to truncation
  EXPECT_EQ(std::strncmp(msg, small_buf, sizeof(small_buf)), 0);
}

}  // namespace fastipc
