cmake_minimum_required(VERSION 3.27)
project("PAO Project" LANGUAGES CXX)

set(TEST_SIZE 2000)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CUDA_STANDARD 23)

set(CMAKE_COLOR_DIAGNOSTICS ON)

set(DEBUG_FLAGS "-O0 -g -Wfatal-errors -Wpedantic -Wall -Wextra -Wconversion -Wshadow=local -Wdouble-promotion -Wformat=2 -Wformat-overflow=2      \
                 -Wformat-nonliteral -Wformat-security -Wformat-truncation=2 -Wnull-dereference -Wimplicit-fallthrough=3 -Wshift-overflow=2        \
                 -Wswitch-default -Wunused-parameter -Wunused-const-variable=2 -Wstrict-overflow=4 -Wstringop-overflow=3 -Wsuggest-attribute=pure  \
                 -Wsuggest-attribute=const -Wsuggest-attribute=noreturn -Wmissing-noreturn -Wsuggest-attribute=malloc -Wsuggest-attribute=format   \
                 -Wmissing-format-attribute -Wsuggest-attribute=cold -Walloc-zero -Walloca -Wattribute-alias=2 -Wduplicated-branches -Wcast-qual   \
                 -fsanitize=address,leak,undefined -march=native")

set(OPTIMIZED_FLAGS "-Ofast -march=native -pipe -fno-builtin -fno-rtti")

set(CMAKE_CXX_FLAGS_DEBUG "${DEBUG_FLAGS}")
set(CMAKE_C_FLAGS_DEBUG "${DEBUG_FLAGS}")

set(CMAKE_CXX_FLAGS_RELEASE "${OPTIMIZED_FLAGS}")
set(CMAKE_C_FLAGS_RELEASE "${OPTIMIZED_FLAGS}")

find_package(OpenMP REQUIRED)
find_package(OpenCL REQUIRED)

add_subdirectory(libs/Graph)
add_subdirectory(libs/Time)
add_subdirectory(libs/OpenCLHelpers)

set(VARIANTS Naive Cached SIMD NaiveOpenMP CachedOpenMP SIMDOpenMP OpenCL OpenCLSwapped)

foreach(VARIANT ${VARIANTS})
    message(STATUS "Configuring ${VARIANT} variant")

    file(GLOB_RECURSE SOURCES ${CMAKE_SOURCE_DIR}/${VARIANT}/*.cpp)
    add_executable(${VARIANT} ${SOURCES})

    target_compile_definitions(${VARIANT} PRIVATE GRAPH_TYPE=float)

    if(DEFINED TEST_SIZE)
        target_compile_definitions(${VARIANT} PRIVATE TEST_SIZE=${TEST_SIZE})
    else()
        target_compile_definitions(${VARIANT} PRIVATE TEST_SIZE=5000)
    endif()

    target_include_directories(${VARIANT} PRIVATE ${CMAKE_SOURCE_DIR}/libs/Graph ${CMAKE_SOURCE_DIR}/libs/Time)

    target_link_libraries(${VARIANT} PRIVATE Graph Time)

    if(VARIANT MATCHES "OpenMP")
        target_link_libraries(${VARIANT} PRIVATE OpenMP::OpenMP_CXX)
    elseif(VARIANT MATCHES "OpenCL")
        target_link_libraries(${VARIANT} PRIVATE OpenCL::OpenCL)
        target_compile_definitions(${VARIANT} PRIVATE CL_HPP_TARGET_OPENCL_VERSION=300)
        target_compile_definitions(${VARIANT} PRIVATE CL_HPP_ENABLE_EXCEPTIONS)
        target_include_directories(${VARIANT} PRIVATE ${CMAKE_SOURCE_DIR}/libs/OpenCLHelpers)
        target_link_libraries(${VARIANT} PRIVATE OpenCLHelpers)
    endif()
endforeach()

