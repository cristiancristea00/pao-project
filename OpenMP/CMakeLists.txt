project(OpenMP)

file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/*.cpp)
add_executable(OpenMP ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE OpenMP::OpenMP_CXX)

