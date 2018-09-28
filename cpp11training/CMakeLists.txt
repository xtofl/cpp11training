cmake_minimum_required(VERSION 3.8)
include("${CMAKE_CURRENT_SOURCE_DIR}/CMake/SetupGoogletest.cmake")

set(CMAKE_CXX_STANDARD 17)
project(cpp11training)
setup_cpp_project_with_googletest("cpp11training")
