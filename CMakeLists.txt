cmake_minimum_required(VERSION 3.10)
project(GameEngine)

set(CMAKE_CXX_STANDARD 17)

# Define directories for third-party libraries
set(GLEW_DIR "${CMAKE_SOURCE_DIR}/Engine/vendor/glew")
set(GLFW_DIR "${CMAKE_SOURCE_DIR}/Engine/vendor/glfw")
set(IMGUI_DIR "${CMAKE_SOURCE_DIR}/Engine/vendor/imgui")
set(ENTT_DIR "${CMAKE_SOURCE_DIR}/Engine/vendor/entt")
set(GLM_DIR "${CMAKE_SOURCE_DIR}/Engine/vendor/glm")

# Include the Engine directory
add_subdirectory(Engine)
add_subdirectory(Editor)
#add_subdirectory(Sandbox)

# Define source files for the executable
set(PROJECT_SOURCES 
    "${CMAKE_SOURCE_DIR}/Engine/src/Core/EntryPoint.cpp"
)

# Create the executable
add_executable(GameEngine ${PROJECT_SOURCES})

# Link the Engine library to the executable
target_link_libraries(GameEngine PRIVATE Engine Editor)

# Include directories
target_include_directories(GameEngine PRIVATE 
    Engine/vendor
    ${GLFW_DIR}/install/include 
    ${GLEW_DIR}/include
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
    ${GLM_DIR}/glm
    ${ENTT_DIR}/src/entt
)

# Compile definitions
target_compile_definitions(GameEngine PRIVATE GLEW_STATIC)

# Link directories
if(WIN32)
    target_link_directories(GameEngine PRIVATE 
        ${GLFW_DIR}/install/lib
        ${GLEW_DIR}/Windows/lib/Release/x64
    )
elseif(UNIX)
    target_link_directories(GameEngine PRIVATE 
        ${GLFW_DIR}/install/lib 
        ${GLEW_DIR}/lib
    )
endif()

# Link libraries based on the operating system
if(WIN32)
    target_link_libraries(GameEngine PRIVATE 
        glew32s 
        glfw3 
        opengl32 
        gdi32 
        winmm
    )
elseif(UNIX)
    target_link_libraries(GameEngine PRIVATE 
        glfw3 
        GLEW 
        m 
        dl 
        pthread 
        GL
    )
else()
    message(FATAL_ERROR "Unsupported operating system")
endif()

