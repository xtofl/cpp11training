cmake_minimum_required(VERSION 2.6)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS -std=c++14)

project(cpp11exercises)


########################### GTEST
# Enable ExternalProject CMake module
INCLUDE(ExternalProject)

# Set default ExternalProject root directory
SET_DIRECTORY_PROPERTIES(PROPERTIES EP_PREFIX ${CMAKE_BINARY_DIR}/third_party)

# Add gtest
# http://stackoverflow.com/questions/9689183/cmake-googletest
ExternalProject_Add(
    gtest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.8.0
    PREFIX gtest
    INSTALL_COMMAND ""
    # Wrap download, configure and build steps in a script to log output
    LOG_DOWNLOAD ON
    LOG_CONFIGURE ON
    LOG_BUILD ON)

# Specify include dir
ExternalProject_Get_Property(gtest source_dir binary_dir)

set(GTEST_INCLUDE_DIR ${source_dir}/googletest/include)
set(GTEST_LIBRARY_PATH ${binary_dir}/${CMAKE_FIND_LIBRARY_PREFIXES}gtest.a)
set_property(TARGET gtest PROPERTY IMPORTED_LOCATION ${GTEST_LIBRARY_PATH} )

include_directories(cpp11training ${GTEST_INCLUDE_DIR})
file (GLOB_RECURSE SOURCES cpp11training/*.cpp)
add_executable(cpp11exercises ${SOURCES})
add_dependencies(cpp11exercises gtest)
target_link_libraries(cpp11exercises ${GTEST_LIBRARY_PATH} pthread)

add_custom_target(unittest ${PROJECT_NAME})
