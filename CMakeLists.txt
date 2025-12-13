cmake_minimum_required(VERSION 3.14)
project(AVL_Trees_Benchmark LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)  # Or 20 if you prefer

include(FetchContent)

FetchContent_Declare(
  googlebenchmark
  GIT_REPOSITORY https://github.com/google/benchmark.git
  GIT_TAG main  # Or a specific tag like v1.8.3
)

# Disable benchmark's own tests
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googlebenchmark)

# Your tree header (adjust path)
add_library(avl_tree INTERFACE)
target_include_directories(avl_tree INTERFACE include/)  # Assuming tree.hpp is in include/

# Benchmark executable
add_executable(benchmarks benchmarks/bench.cpp)  # You'll create this file
target_link_libraries(benchmarks PRIVATE avl_tree benchmark::benchmark benchmark::benchmark_main)