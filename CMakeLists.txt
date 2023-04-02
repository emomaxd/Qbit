cmake_minimum_required(VERSION 3.10)
project(Physics)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#add_compile_options(-O2)

# Add the source files
file(GLOB SOURCES "src/*.cpp")
add_executable(Physics ${SOURCES})
target_link_libraries(Physics raylib)

# Set the output directory for the build files
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})



