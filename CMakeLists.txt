cmake_minimum_required(VERSION 3.27)
project("PAO Project" LANGUAGES C CXX CUDA)

set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CUDA_STANDARD 23)

set(CMAKE_COLOR_DIAGNOSTICS ON)

set(DEBUG_FLAGS "-O0 -g -Wfatal-errors -Wpedantic -Wall -Wextra -Wconversion -Wshadow=local -Wdouble-promotion -Wformat=2 -Wformat-overflow=2      \
                 -Wformat-nonliteral -Wformat-security -Wformat-truncation=2 -Wnull-dereference -Wimplicit-fallthrough=3 -Wshift-overflow=2        \
                 -Wswitch-default -Wunused-parameter -Wunused-const-variable=2 -Wstrict-overflow=4 -Wstringop-overflow=3 -Wsuggest-attribute=pure  \
                 -Wsuggest-attribute=const -Wsuggest-attribute=noreturn -Wmissing-noreturn -Wsuggest-attribute=malloc -Wsuggest-attribute=format   \
                 -Wmissing-format-attribute -Wsuggest-attribute=cold -Walloc-zero -Walloca -Wattribute-alias=2 -Wduplicated-branches -Wcast-qual   \
                 -fsanitize=address,leak,undefined")

set(OPTIMIZED_FLAGS "-Ofast -march=native -pipe -fno-builtin -fopt-info-vec-optimized")

set(CMAKE_CXX_FLAGS_DEBUG "${DEBUG_FLAGS}")
set(CMAKE_C_FLAGS_DEBUG "${DEBUG_FLAGS}")

set(CMAKE_CXX_FLAGS_RELEASE "${OPTIMIZED_FLAGS}")
set(CMAKE_C_FLAGS_RELEASE "${OPTIMIZED_FLAGS}")

if(CMAKE_BUILD_TYPE MATCHES Debug)
    set(CMAKE_C_CLANG_TIDY "clang-tidy;-checks=-*,boost-*,bugprone-* cert-*,clang-analyzer-*,concurrency-*,cppcoreguidelines-*,google-*,hicpp-*,misc-*,modernize-*,mpi-*,openmp-*,performance-*,readability-*")
    set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=-*,boost-*,bugprone-* cert-*,clang-analyzer-*,concurrency-*,cppcoreguidelines-*,google-*,hicpp-*,misc-*,modernize-*,mpi-*,openmp-*,performance-*,readability-*")
endif()

find_package(OpenMP REQUIRED)
find_package(OpenCL REQUIRED)

add_subdirectory(Naive)
add_subdirectory(OpenMP)
add_subdirectory(OpenCL)

