cmake_minimum_required(VERSION 3.15)
project(Tree CXX)

set(CMAKE_CXX_STANDARD 11)

add_executable(Tree_s search_tree.cpp)
add_executable(Tree_e expression_tree.cpp write_log.cpp)
add_executable(Log_dependent  write_log.cpp)
