cmake_minimum_required(VERSION 3.10)
project(Qbit)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(Engine)
add_subdirectory(Editor)
add_subdirectory(Qbit-ScriptCore)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Editor)

set(CMAKE_SUPPRESS_REGENERATION true)