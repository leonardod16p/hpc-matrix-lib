cmake_minimum_required(VERSION 3.10)
project(matrixHPC)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native")

include_directories(include)

add_executable(main apps/main.cpp src/matrix.cpp)