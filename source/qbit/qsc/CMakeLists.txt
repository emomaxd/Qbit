cmake_minimum_required(VERSION 3.8)

# Set the project name and specify C# as the language
project(qsc LANGUAGES CSharp)

# Automatically add all .cs files in the src directory to the project
file(GLOB_RECURSE CS_FILES "source/*.cs")

# Define the C# class library
add_library(qsc SHARED ${CS_FILES})

# Set the output directories for different build configurations
set_target_properties(qsc PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/Editor/Resources/Scripts/"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/Editor/Resources/Scripts/"
)

# Automatically group C# files into folders based on directory structure
foreach(FILE ${CS_FILES})
    # Get the relative path from the root source directory
    file(RELATIVE_PATH REL_PATH ${CMAKE_SOURCE_DIR} ${FILE})

    # Extract directory part from the relative path
    get_filename_component(FOLDER ${REL_PATH} DIRECTORY)

    # Replace "/" with "\\" for Visual Studio folder compatibility
    string(REPLACE "/" "\\" FOLDER ${FOLDER})

    # Assign files to their corresponding folder group
    source_group(${FOLDER} FILES ${FILE})
endforeach()
