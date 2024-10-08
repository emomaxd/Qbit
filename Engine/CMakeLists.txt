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

file(GLOB_RECURSE ENGINE_SRC
    "${CMAKE_SOURCE_DIR}/Engine/src/*.cpp"
    "${CMAKE_SOURCE_DIR}/Engine/src/*.hpp"
    "${CMAKE_SOURCE_DIR}/Engine/src/*.h"
)
file(GLOB IMGUI_SRC
    "${IMGUI_DIR}/*.cpp"
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

add_library(Engine 
    ${ENGINE_SRC}
    ${IMGUI_SRC}
    ${YAML_SRC}
    ${IMGUIZMO_SRC}
    ${BOX2D_SRC}
)

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
    ${ASSIMP_DIR}/build/include
    ${YAML_DIR}/include
    ${IMGUIZMO_DIR}
    ${BOX2D_DIR}/include
    ${MONO_DIR}/include
)

target_compile_definitions(Engine PRIVATE 
    $<$<CONFIG:Debug>:QB_DEBUG>
    $<$<CONFIG:Release>:QB_RELEASE>
    GLEW_STATIC
    YAML_CPP_STATIC_DEFINE
    _CRT_SECURE_NO_WARNINGS
)

if(WIN32)
    target_precompile_headers(Engine PRIVATE "${CMAKE_SOURCE_DIR}/Engine/src/qbpch.h")

    target_compile_definitions(Engine PRIVATE QB_PLATFORM_WINDOWS GLFW_INCLUDE_NONE)

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

    target_link_libraries(Engine PRIVATE 
        opengl32 gdi32 winmm

        glew32s

        $<$<CONFIG:Debug>:glfw3>
        $<$<CONFIG:Release>:glfw3>

        $<$<CONFIG:Debug>:assimp-vc143-mtd>
        $<$<CONFIG:Release>:assimp-vc143-mt>

        $<$<CONFIG:Debug>:zlibstaticd>
        $<$<CONFIG:Release>:zlibstatic>

        $<$<CONFIG:Debug>:libmono-static-sgen>
        $<$<CONFIG:Release>:libmono-static-sgen>
    )
else()
    message(FATAL_ERROR "Unsupported operating system. This configuration is for Windows only.")
endif()