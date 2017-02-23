cmake_minimum_required(VERSION 2.8)

set (CMAKE_CXX_FLAGS "-g -pipe -O2 -std=c++11 -lm")

add_executable(top toposort.cpp)
set_target_properties(top PROPERTIES COMPILER_FLAG ${CMAKE_CXX_FLAGS})
