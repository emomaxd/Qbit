cmake_minimum_required(VERSION 3.10)
project(Engine)

set(CMAKE_CXX_STANDARD 17)

set(GLEW_DIR "${CMAKE_SOURCE_DIR}/Dependencies/GLEW")
set(GLFW_DIR "${CMAKE_SOURCE_DIR}/Dependencies/GLFW")

file(GLOB SOURCES 
"src/Core/*.cpp"
"src/Renderer/*.cpp"
"src/Scene/*.cpp"
"src/System/*.cpp")

add_executable(game ${SOURCES})

target_include_directories(game PRIVATE "Dependencies/glm")
target_include_directories(game PRIVATE "Dependencies/enTT/src")

add_compile_definitions(GLEW_STATIC)


# Linking libraries based on the operating system
if(WIN32)
    # For Windows, link opengl32, gdi32, and winmm
    target_link_libraries(game PRIVATE glew32s glfw3 opengl32 gdi32 winmm)
    target_link_directories(game PRIVATE ${GLFW_DIR}/lib-mingw-w64 ${GLEW_DIR}/lib/Release/x64)
elseif(UNIX)
    # For UNIX-based systems (Linux and macOS), link m, dl, pthread, and GL
    target_link_libraries(game PRIVATE glfw3 GLEW)
    target_link_libraries(game PRIVATE m dl pthread GL)
else()
    message(FATAL_ERROR "Unsupported operating system")
endif()

# Set the output directory for the executable
set_target_properties(game PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build")