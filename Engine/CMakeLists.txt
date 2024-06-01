# Define directories for third-party libraries
set(GLEW_DIR "${CMAKE_SOURCE_DIR}/Engine/vendor/glew")
set(GLFW_DIR "${CMAKE_SOURCE_DIR}/Engine/vendor/glfw")
set(IMGUI_DIR "${CMAKE_SOURCE_DIR}/Engine/vendor/imgui")
set(ENTT_DIR "${CMAKE_SOURCE_DIR}/Engine/vendor/entt")
set(GLM_DIR "${CMAKE_SOURCE_DIR}/Engine/vendor/glm")

# Glob source files
file(GLOB CORE_SRC
    "${CMAKE_SOURCE_DIR}/Engine/src/Core/*.cpp"
    "${CMAKE_SOURCE_DIR}/Engine/src/Core/*.hpp"
)
file(GLOB RENDERER_SRC
    "${CMAKE_SOURCE_DIR}/Engine/src/Renderer/*.cpp"
    "${CMAKE_SOURCE_DIR}/Engine/src/Renderer/*.hpp"
)
file(GLOB SCENE_SRC
    "${CMAKE_SOURCE_DIR}/Engine/src/Scene/*.cpp"
    "${CMAKE_SOURCE_DIR}/Engine/src/Scene/*.hpp"
)
file(GLOB SYSTEM_SRC
    "${CMAKE_SOURCE_DIR}/Engine/src/System/*.cpp"
    "${CMAKE_SOURCE_DIR}/Engine/src/System/*.hpp"
)
file(GLOB IMGUI_SRC
    "${IMGUI_DIR}/*.cpp"
    "${IMGUI_DIR}/backends/imgui_impl_glfw.cpp"
    "${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp"
)

# Group files
source_group("Core" FILES ${CORE_SRC})
source_group("Renderer" FILES ${RENDERER_SRC})
source_group("Scene" FILES ${SCENE_SRC})
source_group("System" FILES ${SYSTEM_SRC})
source_group("ImGui" FILES ${IMGUI_SRC})

# Create Engine library
add_executable(Engine 
    ${CORE_SRC}
    ${RENDERER_SRC}
    ${SCENE_SRC}
    ${SYSTEM_SRC}
    ${IMGUI_SRC}
)

#add_executable(Engine "${CMAKE_SOURCE_DIR}/Engine/src/Core/EntryPoint.hpp")

# Include directories
target_include_directories(Engine PRIVATE 
    ${CMAKE_SOURCE_DIR}/Engine/vendor
    ${GLFW_DIR}/install/include 
    ${GLEW_DIR}/include
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
    ${GLM_DIR}/glm
    ${ENTT_DIR}/src/entt
)

# Compile definitions
target_compile_definitions(Engine PRIVATE GLEW_STATIC)

# Link libraries based on the operating system
if(WIN32)
    target_link_directories(Engine PRIVATE 
        ${GLFW_DIR}/install/lib
        ${GLEW_DIR}/Windows/lib/Release/x64
    )
    target_link_libraries(Engine PRIVATE 
        glew32s 
        glfw3 
        opengl32 
        gdi32 
        winmm
    )
elseif(UNIX)
    target_link_directories(Engine PRIVATE 
        ${GLFW_DIR}/install/lib 
        ${GLEW_DIR}/lib
    )
    target_link_libraries(Engine PRIVATE 
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

# Set the output directory for the executable if needed
#set_target_properties(Engine PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/Out")
