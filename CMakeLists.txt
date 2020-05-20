cmake_minimum_required(VERSION 3.5)

project(3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Python3 REQUIRED COMPONENTS Interpreter Development)
include_directories(3rdparty ${Python3_INCLUDE_DIR})

add_executable(3 main.cpp avl_tree.hpp priority_queue.hpp)
add_executable(test tests.cpp)

add_executable(benchmark benchmark/benchmark.cpp)
target_link_libraries(benchmark ${Python3_LIBRARIES})