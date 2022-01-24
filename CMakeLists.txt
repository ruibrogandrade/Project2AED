cmake_minimum_required(VERSION 3.20)
project(Projeto2AED)

set(CMAKE_CXX_STANDARD 14)

add_executable(Projeto2AED main.cpp GRAPH.h graph.cpp disjointSets.h minHeap.h GraphCreate.cpp GraphCreate.h)
