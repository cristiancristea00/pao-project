cmake_minimum_required(VERSION 3.27)
project(OpenCLHelpers LANGUAGES CXX)

add_library(${PROJECT_NAME} STATIC OpenCLHelpers.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE OpenCL::OpenCL)
target_compile_definitions(${PROJECT_NAME} PRIVATE CL_HPP_TARGET_OPENCL_VERSION=300)
target_compile_definitions(${PROJECT_NAME} PRIVATE CL_HPP_ENABLE_EXCEPTIONS)