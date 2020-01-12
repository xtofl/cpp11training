cmake_minimum_required(VERSION 3.11.0)

set(CMAKE_CXX_STANDARD 17)
project(cpp11training)

include(AddGoogleTest.cmake)

project(cpp11training)
file (GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
add_executable(cpp11training ${SOURCES})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(cpp11training gtest gmock_main)
# target_link_libraries(cpp11training PUBLIC GTest::main)
