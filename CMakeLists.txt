cmake_minimum_required (VERSION 3.11.2)
project (QM)
set(CMAKE_CXX_COMPILER     "/usr/bin/clang++-6.0")
set(CMAKE_CXX_FlAGS        "-g -O3 -Wall -lstdc++ -std=c++2a")

add_subdirectory(kernels)
