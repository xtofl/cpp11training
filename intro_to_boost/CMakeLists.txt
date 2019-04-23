cmake_minimum_required(VERSION 2.8.12)
project(thejourney)

add_definitions("-std=c++17")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(thejourney journey.cpp)
target_link_libraries(thejourney ${CONAN_LIBS})