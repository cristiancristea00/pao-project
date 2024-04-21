project(OpenCL)

file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/*.cpp)
add_executable(OpenCL ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE OpenCL::OpenCL)
target_compile_definitions(${PROJECT_NAME} PRIVATE CL_HPP_TARGET_OPENCL_VERSION=300)
target_compile_definitions(${PROJECT_NAME} PRIVATE CL_HPP_ENABLE_EXCEPTIONS)

