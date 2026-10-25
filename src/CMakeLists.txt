cmake_minimum_required(VERSION 3.30.0)

set(CMAKE_CXX_STANDARD 20)
project(cpp11training)


project(cpp11training)
file (GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
add_executable(cpp11training ${SOURCES})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

include(FetchGoogleTest.cmake)
fetch_google_test()
target_link_libraries(cpp11training gtest)
