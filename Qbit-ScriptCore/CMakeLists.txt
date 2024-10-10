cmake_minimum_required(VERSION 3.8)

# Set the project name and specify C# as the language
project(Qbit-ScriptCore LANGUAGES CSharp)

# Automatically add all .cs files in the src directory to the project
file(GLOB_RECURSE CS_FILES "${CMAKE_SOURCE_DIR}/Qbit-ScriptCore/Source/*.cs")

# Define the C# class library
add_library(Qbit-ScriptCore SHARED ${CS_FILES})

set_target_properties(Qbit-ScriptCore PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/Editor/Resources/Scripts/")
set_target_properties(Qbit-ScriptCore PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/Editor/Resources/Scripts/")