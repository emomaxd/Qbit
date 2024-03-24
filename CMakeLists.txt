cmake_minimum_required(VERSION 3.10)
project(GameEngine)

set(CMAKE_CXX_STANDARD 17)

# Include subdirectories
add_subdirectory(Engine)
# add_subdirectory(Editor) # Currently not present
add_subdirectory(Vendor/glfw)
add_subdirectory(Vendor/imgui)

# Set the location for the main function
set(MAIN_FILE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/Engine/src/Core/EntryPoint.cpp")

# Define the executable target and specify the main file
add_executable(GameEngine ${MAIN_FILE_PATH})


target_include_directories(GameEngine PUBLIC Vendor)
target_include_directories(GameEngine PUBLIC Vendor/glfw/include)
target_include_directories(GameEngine PUBLIC Vendor/imgui)
target_include_directories(GameEngine PUBLIC Vendor/enTT/src/entt)
target_include_directories(GameEngine PUBLIC Vendor/glm)
target_include_directories(GameEngine PUBLIC Vendor/GLEW/include)

add_compile_definitions(GLEW_STATIC)

target_link_directories(GameEngine 
PUBLIC build/Vendor/glfw/src/Debug 
PUBLIC Vendor/GLEW/lib/Release/x64
)
# Link the executable with the Engine libraries and glfw
target_link_libraries(GameEngine PUBLIC Core Renderer Scene ImGui glfw glew32s opengl32 gdi32 winmm)
