cmake_minimum_required(VERSION 3.11.0)

set(CMAKE_CXX_STANDARD 17)
project(cpp11training)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.8.0
)
FetchContent_MakeAvailable(googletest)
FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
  FetchContent_Populate(googletest)
  add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif()

project(cpp11training)
file (GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
add_executable(cpp11training ${SOURCES})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(cpp11training gtest gmock_main)
# target_link_libraries(cpp11training PUBLIC GTest::main)
