cmake_minimum_required(VERSION 3.10)
project(Qbit)

set(CMAKE_CXX_STANDARD 17)

# Include the Engine directory
add_subdirectory(Engine)
add_subdirectory(Editor)
add_subdirectory(Sandbox)
add_subdirectory(Qbit-ScriptCore)
add_subdirectory(Editor/SandboxProject/Assets/Scripts)

# Set Engine as the startup project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Editor)

# Remove ALL_BUILD and ZERO_CHECK targets
set(CMAKE_SUPPRESS_REGENERATION true)

set(CMAKE_CONFIGURATION_TYPES Debug Release CACHE STRING "" FORCE)