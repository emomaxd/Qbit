# Define directories for third-party libraries
set(GLEW_DIR "${CMAKE_SOURCE_DIR}/Engine/vendor/glew")
set(GLFW_DIR "${CMAKE_SOURCE_DIR}/Engine/vendor/glfw")
set(IMGUI_DIR "${CMAKE_SOURCE_DIR}/Engine/vendor/imgui")
set(ENTT_DIR "${CMAKE_SOURCE_DIR}/Engine/vendor/entt")
set(GLM_DIR "${CMAKE_SOURCE_DIR}/Engine/vendor/glm")
set(ASSIMP_DIR "${CMAKE_SOURCE_DIR}/Engine/vendor/assimp")
set(YAML_DIR "${CMAKE_SOURCE_DIR}/Engine/vendor/yaml-cpp")
set(IMGUIZMO_DIR "${CMAKE_SOURCE_DIR}/Engine/vendor/ImGuizmo")
set(BOX2D_DIR "${CMAKE_SOURCE_DIR}/Engine/vendor/Box2D")
set(MONO_DIR "${CMAKE_SOURCE_DIR}/Engine/vendor/mono")

# Glob source files
file(GLOB_RECURSE ENGINE_SRC
    "${CMAKE_SOURCE_DIR}/Engine/src/*.cpp"
    "${CMAKE_SOURCE_DIR}/Engine/src/*.hpp"
    "${CMAKE_SOURCE_DIR}/Engine/src/*.h"
)
file(GLOB IMGUI_SRC
    "${IMGUI_DIR}/*.cpp"
    "${IMGUI_DIR}/backends/imgui_impl_glfw.cpp"
    "${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp"
)
file(GLOB YAML_SRC
    "${YAML_DIR}/src/*.cpp"
    "${YAML_DIR}/src/*.h"
    "${YAML_DIR}/include/*.h"
)
file(GLOB IMGUIZMO_SRC
    "${IMGUIZMO_DIR}/*.cpp"
    "${IMGUIZMO_DIR}/*.h"
)
file(GLOB BOX2D_SRC
    "${BOX2D_DIR}/src/*/*.cpp"
    "${BOX2D_DIR}/include/*.h"
)

# Create Engine library
add_library(Engine 
    ${ENGINE_SRC}
    ${IMGUI_SRC}
    ${YAML_SRC}
    ${IMGUIZMO_SRC}
    ${BOX2D_SRC}
)

# Include directories
target_include_directories(Engine PRIVATE 
    ${CMAKE_SOURCE_DIR}/Engine
    ${CMAKE_SOURCE_DIR}/Engine/src
    ${CMAKE_SOURCE_DIR}/Engine/vendor
    ${CMAKE_SOURCE_DIR}/Engine/vendor/spdlog/include
    ${GLFW_DIR}/include 
    ${GLEW_DIR}/include
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
    ${GLM_DIR}/glm
    ${GLM_DIR}
    ${ENTT_DIR}/src/entt
    ${ASSIMP_DIR}/include
    ${YAML_DIR}/include
    ${IMGUIZMO_DIR}
    ${BOX2D_DIR}/include
    ${MONO_DIR}/include
)

# Compile definitions
target_compile_definitions(Engine PRIVATE GLEW_STATIC YAML_CPP_STATIC_DEFINE)

# Define QB_DEBUG for Debug configuration only
target_compile_definitions(Engine PRIVATE 
    $<$<CONFIG:Debug>:QB_DEBUG>
    _CRT_SECURE_NO_WARNINGS
)

# Set up library directories and linking for Windows only
if(WIN32)
    # Use precompiled headers
    target_precompile_headers(Engine PRIVATE "${CMAKE_SOURCE_DIR}/Engine/src/qbpch.h")

    # Set compile definitions for Windows-specific configurations
    target_compile_definitions(Engine PRIVATE QB_PLATFORM_WINDOWS GLFW_INCLUDE_NONE)

    # Link directories for Debug and Release configurations separately
    target_link_directories(Engine PRIVATE 
        $<$<CONFIG:Debug>:${GLFW_DIR}/build/src/Debug>
        $<$<CONFIG:Release>:${GLFW_DIR}/build/src/Release>
        
        $<$<CONFIG:Debug>:${GLEW_DIR}/Windows/lib/Debug/x64>
        $<$<CONFIG:Release>:${GLEW_DIR}/Windows/lib/Release/x64>
        
        $<$<CONFIG:Debug>:${ASSIMP_DIR}/build/lib/Debug>
        $<$<CONFIG:Release>:${ASSIMP_DIR}/build/lib/Release>

        $<$<CONFIG:Debug>:${ASSIMP_DIR}/contrib/zlib/Debug>
        $<$<CONFIG:Release>:${ASSIMP_DIR}/contrib/zlib/Release>
        
        $<$<CONFIG:Debug>:${MONO_DIR}/lib/Debug>
        $<$<CONFIG:Release>:${MONO_DIR}/lib/Release>
    )

    # Link libraries based on the configuration
    target_link_libraries(Engine PRIVATE 
        # Static OpenGL and Windows-specific libraries
        opengl32 gdi32 winmm

        # GLEW (static library)
        glew32s

        # GLFW (Debug or Release)
        $<$<CONFIG:Debug>:glfw3>
        $<$<CONFIG:Release>:glfw3>

        # Assimp (Debug or Release)
        $<$<CONFIG:Debug>:assimp-vc143-mtd>
        $<$<CONFIG:Release>:assimp-vc143-mt>

        # Zlib for Assimp (Debug or Release)
        $<$<CONFIG:Debug>:zlibstaticd>
        $<$<CONFIG:Release>:zlibstatic>

        # Mono (Debug or Release)
        $<$<CONFIG:Debug>:libmono-static-sgen>
        $<$<CONFIG:Release>:libmono-static-sgen>
    )
else()
    message(FATAL_ERROR "Unsupported operating system. This configuration is for Windows only.")
endif()