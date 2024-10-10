cmake_minimum_required(VERSION 3.8)

# Set the project name and specify C# as the language
project(SandboxProject LANGUAGES CSharp)

# Automatically add all .cs files in the src directory to the project
file(GLOB_RECURSE CS_FILES "${CMAKE_CURRENT_SOURCE_DIR}/Source/*.cs")

# Define the C# class library
add_library(SandboxProject SHARED ${CS_FILES})

set_property(TARGET SandboxProject PROPERTY 
    VS_DOTNET_REFERENCE_Qbit-ScriptCore "${CMAKE_CURRENT_SOURCE_DIR}/Binaries/Qbit-ScriptCore.dll")

# Set output directories
set_target_properties(SandboxProject PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/Binaries/")
set_target_properties(SandboxProject PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/Binaries/")