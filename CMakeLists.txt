cmake_minimum_required(VERSION 3.15)
project(MPI)

set(CMAKE_CXX_STANDARD 11)
include_directories(/usr/local/Cellar/mpich/3.3.2/include)

add_executable(MPI main.cpp)