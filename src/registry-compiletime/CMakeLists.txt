file(GLOB_RECURSE src ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
get_filename_component(exec_name ${CMAKE_CURRENT_SOURCE_DIR} NAME)
add_executable(${exec_name} ${src})

set_property(TARGET ${exec_name} 
    PROPERTY 
    CXX_STANDARD 17
)

set_target_properties(${exec_name} PROPERTIES COMPILE_FLAGS "--save-temps")