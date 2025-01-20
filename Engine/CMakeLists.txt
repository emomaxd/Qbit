project(Engine)

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

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/msdf-atlas-gen)

# Combine all sources
add_library(Engine 
    ${ENGINE_SRC}
    ${IMGUI_SRC}
    ${YAML_SRC}
    ${IMGUIZMO_SRC}
    ${BOX2D_SRC}
)

target_compile_options(Engine PRIVATE 
    $<$<CONFIG:Debug>:/MDd>   # Debug mode: Multi-threaded Debug DLL
    $<$<CONFIG:Release>:/MD>   # Release mode: Multi-threaded DLL
)

# Find the Vulkan SDK
find_package(Vulkan REQUIRED)
get_filename_component(VULKAN_LIB_DIR ${Vulkan_LIBRARIES} DIRECTORY)

# Optionally, print out the Vulkan library directory for debugging purposes
# message(STATUS "Vulkan library directory: ${VULKAN_LIB_DIR}")

# Add Vulkan include directories
include_directories(${Vulkan_INCLUDE_DIRS})

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

    target_compile_definitions(Engine PRIVATE 
        QB_PLATFORM_WINDOWS
        GLFW_INCLUDE_NONE
        $<$<CONFIG:Debug>:_ITERATOR_DEBUG_LEVEL=2>  # Debug mode
        $<$<CONFIG:Release>:_ITERATOR_DEBUG_LEVEL=0> # Release mode
    )

    target_link_directories(Engine PRIVATE 
        
        $<$<CONFIG:Debug>:${GLEW_DIR}/Windows/lib/Debug/x64>
        $<$<CONFIG:Release>:${GLEW_DIR}/Windows/lib/Release/x64>
        $<$<CONFIG:Debug>:${MONO_DIR}/lib/Debug>
        $<$<CONFIG:Release>:${MONO_DIR}/lib/Release>
        ${VULKAN_LIB_DIR}
    )

    target_link_libraries(Engine PRIVATE 
        opengl32 gdi32 winmm
        glew32s
        
        vulkan-1
        msdf-atlas-gen

        assimp
        glfw

        # SPIRV-Tools Debug and Release libraries
        $<$<CONFIG:Debug>:SPIRV-Toolsd>
        $<$<CONFIG:Release>:SPIRV-Tools>
        $<$<CONFIG:Debug>:SPIRV-Tools-optd>
        $<$<CONFIG:Release>:SPIRV-Tools-opt>
        $<$<CONFIG:Debug>:SPIRV>
        $<$<CONFIG:Release>:SPIRV>
        
        # SPIRV-Cross Debug and Release libraries
        $<$<CONFIG:Debug>:spirv-cross-cored>
        $<$<CONFIG:Release>:spirv-cross-core>
        $<$<CONFIG:Debug>:spirv-cross-glsld>
        $<$<CONFIG:Release>:spirv-cross-glsl>
        
        # GLSLang Debug and Release libraries
        $<$<CONFIG:Debug>:glslangd>
        $<$<CONFIG:Release>:glslang>

        # ShaderC Debug and Release libraries
        $<$<CONFIG:Debug>:shadercd>
        $<$<CONFIG:Release>:shaderc>
        $<$<CONFIG:Debug>:shaderc_utild>
        $<$<CONFIG:Release>:shaderc_util>

        $<$<CONFIG:Debug>:libmono-static-sgen>
        $<$<CONFIG:Release>:libmono-static-sgen>
    )
else()
    message(FATAL_ERROR "Unsupported operating system. This configuration is for Windows only.")
endif()

# Enable Visual Studio folder support and show all files
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(TARGET Engine PROPERTY VS_SOLUTION_SHOW_ALL_FILES ON)
