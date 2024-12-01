project(Editor)

# Vendor directories
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
set(MSDF_ATLAS_GEN_DIR "${CMAKE_SOURCE_DIR}/Engine/vendor/msdf-atlas-gen")

# Gather source files for Engine
file(GLOB_RECURSE ENGINE_SRC
    "${CMAKE_SOURCE_DIR}/Engine/src/*.cpp"
    "${CMAKE_SOURCE_DIR}/Engine/src/*.hpp"
    "${CMAKE_SOURCE_DIR}/Engine/src/*.h"
)

# Gather source files for specific libraries (imgui, yaml, etc.)
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

# Combine all sources
add_library(Engine 
    ${ENGINE_SRC}
    ${IMGUI_SRC}
    ${YAML_SRC}
    ${IMGUIZMO_SRC}
    ${BOX2D_SRC}
)

# Automatically group files into logical folders in Visual Studio
foreach(FILE ${ENGINE_SRC} ${IMGUI_SRC} ${YAML_SRC} ${IMGUIZMO_SRC} ${BOX2D_SRC})
    # Get the relative path from the root source directory
    file(RELATIVE_PATH REL_PATH ${CMAKE_SOURCE_DIR} ${FILE})

    # Extract directory part from the relative path
    get_filename_component(FOLDER ${REL_PATH} DIRECTORY)

    # Replace "/" with "\\" for Visual Studio folder compatibility
    string(REPLACE "/" "\\" FOLDER ${FOLDER})

    # Assign files to their corresponding folder group
    source_group(${FOLDER} FILES ${FILE})
endforeach()

# Include directories for Engine and dependencies
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
    ${MSDF_ATLAS_GEN_DIR}/include
    ${MSDF_ATLAS_GEN_DIR}/msdf-atlas-gen
    ${MSDF_ATLAS_GEN_DIR}/msdfgen
)

# Define compile-time flags for debugging and release configurations
target_compile_definitions(Engine PRIVATE 
    $<$<CONFIG:Debug>:QB_DEBUG>
    $<$<CONFIG:Release>:QB_RELEASE>
    GLEW_STATIC
    YAML_CPP_STATIC_DEFINE
    _CRT_SECURE_NO_WARNINGS
)

# Platform-specific configurations for Windows
if(WIN32)
    target_precompile_headers(Engine PRIVATE "${CMAKE_SOURCE_DIR}/Engine/src/qbpch.h")

    target_compile_definitions(Engine PRIVATE QB_PLATFORM_WINDOWS GLFW_INCLUDE_NONE)

    target_link_directories(Engine PRIVATE 
        ${MSDF_ATLAS_GEN_DIR}
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
        freetype
        libpng16
        skia.dll.lib
        $<$<CONFIG:Debug>:msdfgen-cored>
        $<$<CONFIG:Release>:msdfgen-core>
        $<$<CONFIG:Debug>:msdfgen-extd>
        $<$<CONFIG:Release>:msdfgen-ext>
        $<$<CONFIG:Debug>:msdf-atlas-gend>
        $<$<CONFIG:Release>:msdf-atlas-gen>
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

# Enable Visual Studio folder support and show all files
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(TARGET Engine PROPERTY VS_SOLUTION_SHOW_ALL_FILES ON)
