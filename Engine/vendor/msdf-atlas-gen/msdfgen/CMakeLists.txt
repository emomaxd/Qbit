# MSDFGEN project

cmake_minimum_required(VERSION 3.10)

project(msdfgen)


set(CMAKE_CXX_STANDARD 17)

# Static library
file(GLOB MSDFGEN_SRC
    core/*.h
    core/*.hpp
    core/*.cpp
    ext/*.h
    ext/*.hpp
    ext/*.cpp
    lib/*.cpp
    include/*.h
)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/freetype)




add_library(msdfgen STATIC ${MSDFGEN_SRC})

# Include directories
target_include_directories(msdfgen PUBLIC
    include
    freetype/include
)

# Preprocessor defines
target_compile_definitions(msdfgen PRIVATE
    MSDFGEN_USE_CPP11
)

# Link libraries
target_link_libraries(msdfgen PRIVATE
    freetype
)

# Linker settings (for Windows)
if(WIN32)
    set_target_properties(msdfgen PROPERTIES
        SYSTEM_VERSION "latest"
    )
endif()

# Set runtime library to avoid mismatches (MD for Release, MDd for Debug)
target_compile_options(msdfgen PRIVATE 
    $<$<CONFIG:Debug>:/MDd>   # Debug mode: Multi-threaded Debug DLL
    $<$<CONFIG:Release>:/MD>   # Release mode: Multi-threaded DLL
)

# Set build types
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")
set(CMAKE_CXX_FLAGS_DIST "-O3")
