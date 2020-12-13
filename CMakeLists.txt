cmake_minimum_required(VERSION 3.14 FATAL_ERROR)
project(registry)

set(src_dir "${PROJECT_SOURCE_DIR}/src")

add_subdirectory(${src_dir}/registry-runtime 
    ${CMAKE_BINARY_DIR}/registry-runtime
)
add_subdirectory(${src_dir}/registry-compiletime 
    ${CMAKE_BINARY_DIR}/registry-compiletime
)
