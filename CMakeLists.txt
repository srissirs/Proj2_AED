cmake_minimum_required(VERSION 3.20)
project(proj2AED)

set(CMAKE_CXX_STANDARD 14)

add_executable(proj2AED codigo/main.cpp codigo/scr/Graph.cpp codigo/scr/Graph.h codigo/scr/minHeap.h codigo/scr/readFiles.cpp codigo/scr/readFiles.h)
