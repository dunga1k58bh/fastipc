add_library(fastipc STATIC
  core/simple_channel.cc
  core/shared_memory.cc
  # any other implementation files
)

target_include_directories(fastipc
  PUBLIC ${CMAKE_SOURCE_DIR}/include
  PUBLIC ${CMAKE_SOURCE_DIR}/src
)

target_compile_features(fastipc PUBLIC cxx_std_17)