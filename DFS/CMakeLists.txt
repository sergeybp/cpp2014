cmake_minimum_required(VERSION 2.8)
project(DFS)
include_directories(${DFS_SOURCE_DIR})

add_executable(test main.cpp
graph/graph.cpp graph/graph.h
node/node.cpp node/node.h
edge/edge.h edge/edge.cpp
gtest/gtest-all.cc gtest/gtest.h gtest/gtest_main.cc)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++0x -pedantic -O3")

target_link_libraries(test -lpthread)
