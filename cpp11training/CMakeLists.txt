cmake_minimum_required(VERSION 2.6)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(cpp11exercises)

set (GTEST_DIR dependencies/googletest/googletest)
include_directories(${GTEST_DIR}/include ${GTEST_DIR})
add_library(gtest ${GTEST_DIR}/src/gtest-all.cc)
target_link_libraries(gtest pthread)

include_directories(cpp11training)
file (GLOB SOURCES cpp11training/*.cpp)
add_executable(cpp11exercises ${SOURCES})
target_link_libraries(cpp11exercises gtest)

