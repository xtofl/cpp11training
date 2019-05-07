cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_CXX_STANDARD 17)
project(coupled_program)

add_library(graphs coupled_program/graphs/graph.cpp)

add_executable(coupled_program coupled_program/deps.cpp)
target_link_libraries(coupled_program LINK_PUBLIC graphs)