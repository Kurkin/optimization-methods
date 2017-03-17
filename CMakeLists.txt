cmake_minimum_required(VERSION 3.6)
project(optimize)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES search.cpp)
add_executable(search ${SOURCE_FILES})
add_executable(newton newton.cpp)
