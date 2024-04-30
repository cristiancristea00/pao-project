cmake_minimum_required(VERSION 3.27)
project(Graph LANGUAGES CXX)

add_library(${PROJECT_NAME} STATIC Graph.cpp)
target_compile_definitions(${PROJECT_NAME} PRIVATE GRAPH_TYPE=float)