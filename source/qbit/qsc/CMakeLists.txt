cmake_minimum_required(VERSION 3.8)

# Set the project name and specify C# as the language
project(qsc LANGUAGES CSharp)

# Automatically add all .cs files in the src directory to the project
file(GLOB_RECURSE CS_FILES "source/*.cs")

# Define the C# class library
add_library(qsc SHARED ${CS_FILES})

# Set the output directories for different build configurations
set_target_properties(qsc PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/source/creator/resources/scripts/"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/source/creator/resources/scripts/"
)