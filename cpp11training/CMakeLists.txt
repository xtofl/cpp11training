
cmake_minimum_required(VERSION 2.6)

project(cpp11exercises)
add_definitions(-std=c++11)

set (GTEST_DIR dependencies/googletest/googletest)
include_directories(${GTEST_DIR}/include)
add_library(gtest ${GTEST_DIR}/src/gtest-all.cc)

include_directories(cpp11training)
file (GLOB SOURCES cpp11training/*.cpp)
add_executable(cpp11exercises ${SOURCES})
target_link_libraries(cpp11exercises gtest-all)

