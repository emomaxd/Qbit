cmake_minimum_required(VERSION 3.8)

project(SandboxProject LANGUAGES CSharp)

file(GLOB_RECURSE CS_FILES "${CMAKE_CURRENT_SOURCE_DIR}/Assets/Scripts/*.cs")

add_library(SandboxProject SHARED ${CS_FILES})

cmake_path(GET CMAKE_CURRENT_SOURCE_DIR PARENT_PATH current_parent)
cmake_path(GET current_parent PARENT_PATH project_dir)

set_property(TARGET SandboxProject PROPERTY 
    VS_DOTNET_REFERENCE_Qbit-ScriptCore "${CMAKE_CURRENT_SOURCE_DIR}/Library/Qbit-ScriptCore.dll")

set_target_properties(SandboxProject PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/Library"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/Library/")
