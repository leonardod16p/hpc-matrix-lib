cmake_minimum_required(VERSION 3.14)
project(matrixHPC LANGUAGES CXX CUDA)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CUDA_STANDARD 17)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-tree-vectorize -march=native")

include_directories(include)

add_executable(main apps/main.cpp src/matrix.cpp src/hello.cu)

include(FetchContent)
FetchContent_Declare(
  googlebenchmark
  GIT_REPOSITORY https://github.com/google/benchmark.git
  GIT_TAG v1.8.3
)

set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googlebenchmark)

add_executable(bench_matrix benchmarks/bench_matrix.cpp src/matrix.cpp src/hello.cu)

target_link_libraries(bench_matrix PRIVATE benchmark::benchmark_main)