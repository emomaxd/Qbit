cmake_minimum_required(VERSION 3.10)

project(msdf-atlas-gen)

# Set C++ standard and runtime options
set(CMAKE_CXX_STANDARD 17)

# Create a static library for msdf-atlas-gen
file(GLOB MSDF_ATLAS_GEN_SRC
    msdf-atlas-gen/*.h
    msdf-atlas-gen/*.hpp
    msdf-atlas-gen/*.cpp
)

add_subdirectory(msdfgen)




add_library(msdf-atlas-gen STATIC ${MSDF_ATLAS_GEN_SRC})

# Include directories for msdf-atlas-gen
target_include_directories(msdf-atlas-gen PUBLIC
    msdf-atlas-gen
    msdfgen
    msdfgen/include
)

# Preprocessor defines
target_compile_definitions(msdf-atlas-gen PUBLIC
    _CRT_SECURE_NO_WARNINGS
)

# Link msdfgen library
target_link_libraries(msdf-atlas-gen PUBLIC
    msdfgen
)

# Linker settings for Windows
if(WIN32)
    set_target_properties(msdf-atlas-gen PROPERTIES
        SYSTEM_VERSION "latest"
    )
endif()

# Set runtime library to avoid mismatches (MD for Release, MDd for Debug)
target_compile_options(msdf-atlas-gen PUBLIC 
    $<$<CONFIG:Debug>:/MDd>   # Debug mode: Multi-threaded Debug DLL
    $<$<CONFIG:Release>:/MD>   # Release mode: Multi-threaded DLL
)

# Build configurations
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")
set(CMAKE_CXX_FLAGS_DIST "-O3")
