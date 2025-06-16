# Locate GTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
)
FetchContent_MakeAvailable(googletest)

# Test executable
add_executable(core_unittest
  core/shared_memory_unittest.cc
  core/simple_channel_unittest.cc
  # Add other test files here as needed
)

# Link with GTest and FastIPC
target_link_libraries(core_unittest
  PRIVATE
    gtest
    gtest_main
    fastipc
)

# Register with CTest (optional)
enable_testing()
add_test(NAME CoreUnitTests COMMAND core_unittest)