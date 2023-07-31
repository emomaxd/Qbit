cmake_minimum_required(VERSION 3.10)
project(Engine)

set(CMAKE_CXX_STANDARD 17)

set(RAYLIB_DIR "${CMAKE_SOURCE_DIR}/Dependencies/Raylib")


file(GLOB SOURCES "src/*.cpp")

link_directories(${RAYLIB_DIR}/lib)

add_executable(game ${SOURCES})
target_link_libraries(game raylib opengl32 gdi32 winmm)

set_target_properties(game PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build")



