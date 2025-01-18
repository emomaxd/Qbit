# Prevent in-source builds
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR} AND NOT DEFINED WITH_IN_SOURCE_BUILD)
  message(FATAL_ERROR
    "CMake generation for Qbit is not allowed within the source directory!"
    "\nRemove the CMakeCache.txt and CMakeFiles directories and build out-of-source."
    "\nExample:"
    "\n mkdir build && cd build && cmake .."
  )
endif()

cmake_minimum_required(VERSION 3.10)
project(Qbit)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17 CACHE STRING "C++ standard" FORCE)

# Add subdirectories
add_subdirectory(Engine)
add_subdirectory(Editor)
add_subdirectory(Qbit-ScriptCore)

# Set the default startup project for Visual Studio
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Editor)

# Optional: Platform-specific configurations
if(WIN32)
  # Windows-specific setup
elseif(UNIX)
  # Linux-specific setup
endif()

# Optional: Set build type
set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose build type" FORCE)

# Optional: Suppress regeneration if necessary (keep this only if needed)
# set(CMAKE_SUPPRESS_REGENERATION true)
