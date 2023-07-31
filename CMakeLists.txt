cmake_minimum_required(VERSION 3.10)
project(Engine)

set(CMAKE_CXX_STANDARD 17)

set(RAYLIB_DIR "${CMAKE_SOURCE_DIR}/Dependencies/Raylib")
file(GLOB SOURCES "src/*.cpp")

add_executable(game ${SOURCES})

# Linking libraries based on the operating system
if(WIN32)
    # For Windows, link raylib, opengl32, gdi32, and winmm
    link_directories(${RAYLIB_DIR}/lib)
    target_link_libraries(game raylib opengl32 gdi32 winmm)
elseif(UNIX)
    # For Linux, link raylib, m, dl, rt, X11, pthread, and GL
    target_link_libraries(game raylib m dl rt X11 pthread GL)
else()
    message(FATAL_ERROR "Unsupported operating system")
endif()

# Set the output directory for the executable
set_target_properties(game PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build")
