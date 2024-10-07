cmake_minimum_required(VERSION 3.8)

# Set the project name and specify C# as the language
project(SandboxProject LANGUAGES CSharp)

# Automatically add all .cs files in the src directory to the project
file(GLOB_RECURSE CS_FILES "${CMAKE_SOURCE_DIR}/Editor/SandboxProject/Assets/Scripts/Source/*.cs")

# Define the C# class library
add_library(SandboxProject SHARED ${CS_FILES})

target_link_libraries(SandboxProject PRIVATE Qbit-ScriptCore)

set_target_properties(SandboxProject PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/Editor/SandboxProject/Assets/Scripts/Binaries/")
set_target_properties(SandboxProject PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/Editor/SandboxProject/Assets/Scripts/Binaries/")