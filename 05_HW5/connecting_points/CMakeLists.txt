cmake_minimum_required(VERSION 2.8)

set (CMAKE_CXX_FLAGS "-g -pipe -O2 -std=c++11 -lm")

add_executable(disjoint disjoint_set.cpp)
set_target_properties(disjoint PROPERTIES COMPILER_FLAG ${CMAKE_CXX_FLAGS})
