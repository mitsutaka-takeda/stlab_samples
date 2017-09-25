cmake_minimum_required (VERSION 3.6)
project (stlab_sample LANGUAGES CXX)

find_package(Boost)
find_package(Threads)

add_executable(
  channel_sample
  channel_sample.cpp
  )

target_include_directories(
  channel_sample
  PUBLIC
  ../libraries/
  ../range-v3/include
  )
target_link_libraries(
  channel_sample
  PUBLIC
  Boost::boost
  Threads::Threads
  )

add_executable(
  channel_sample_2
  channel_sample_2.cpp
  )

target_include_directories(
  channel_sample_2
  PUBLIC
  ../libraries/
  ../range-v3/include
  )

target_link_libraries(
  channel_sample_2
  PUBLIC
  Boost::boost
  Threads::Threads
  )

add_executable(
  channel_sample_3
  channel_sample_3.cpp
  )

target_include_directories(
  channel_sample_3
  PUBLIC
  ../libraries/
  ../range-v3/include
  )

target_link_libraries(
  channel_sample_3
  PUBLIC
  Boost::boost
  Threads::Threads
  )

add_executable(
  async_sample
  async_sample.cpp
  )

target_include_directories(
  async_sample
  PUBLIC
  ../libraries/
  )
target_link_libraries(
  async_sample
  PUBLIC
  Boost::boost
  Threads::Threads
  )
