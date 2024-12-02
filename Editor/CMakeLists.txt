# Vendor directories
set(GLEW_DIR "${CMAKE_SOURCE_DIR}/Engine/vendor/glew")
set(GLFW_DIR "${CMAKE_SOURCE_DIR}/Engine/vendor/glfw")
set(IMGUI_DIR "${CMAKE_SOURCE_DIR}/Engine/vendor/imgui")
set(ENTT_DIR "${CMAKE_SOURCE_DIR}/Engine/vendor/entt")
set(GLM_DIR "${CMAKE_SOURCE_DIR}/Engine/vendor/glm")
set(ASSIMP_DIR "${CMAKE_SOURCE_DIR}/Engine/vendor/assimp")
set(IMGUIZMO_DIR "${CMAKE_SOURCE_DIR}/Engine/vendor/ImGuizmo")
set(MONO_DIR "${CMAKE_SOURCE_DIR}/Engine/vendor/mono")
set(MSDF_ATLAS_GEN_DIR "${CMAKE_SOURCE_DIR}/Engine/vendor/msdf-atlas-gen")

# Gather all source files
file(GLOB_RECURSE CORE_SOURCES "*.cpp" "*.cxx" "*.cc" "*.hpp" "*.h")

# Find the Vulkan SDK
find_package(Vulkan REQUIRED)
get_filename_component(VULKAN_LIB_DIR ${Vulkan_LIBRARIES} DIRECTORY)

# Add Vulkan include directories
include_directories(${Vulkan_INCLUDE_DIRS})

# Group files based on folder structure
foreach(FILE ${CORE_SOURCES})
    # Get the relative path from the root source directory
    file(RELATIVE_PATH REL_PATH ${CMAKE_SOURCE_DIR} ${FILE})

    # Extract directory part from the relative path
    get_filename_component(FOLDER ${REL_PATH} DIRECTORY)

    # Replace "/" with "\\" for Visual Studio
    string(REPLACE "/" "\\" FOLDER ${FOLDER})

    # Assign files to their respective groups
    source_group(${FOLDER} FILES ${FILE})
endforeach()

# Add the executable
add_executable(Editor ${CORE_SOURCES})

# Include directories
target_include_directories(Editor PRIVATE 
    ${CMAKE_SOURCE_DIR}/Engine
    ${CMAKE_SOURCE_DIR}/Engine/src
    ${CMAKE_SOURCE_DIR}/Engine/vendor
    ${CMAKE_SOURCE_DIR}/Engine/vendor/spdlog/include
    ${GLFW_DIR}/install/include 
    ${GLEW_DIR}/include
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
    ${GLM_DIR}
    ${GLM_DIR}/glm
    ${ENTT_DIR}/src/entt
    ${ASSIMP_DIR}/include
    ${ASSIMP_DIR}/build/include
    ${IMGUIZMO_DIR}
    ${MONO_DIR}/include
    ${MSDF_ATLAS_GEN_DIR}/include
    ${MSDF_ATLAS_GEN_DIR}/msdf-atlas-gen
    ${MSDF_ATLAS_GEN_DIR}/msdfgen
)

# Compile definitions
target_compile_definitions(Editor PRIVATE 
    $<$<CONFIG:Debug>:QB_DEBUG>
    $<$<CONFIG:Release>:QB_RELEASE>
    GLEW_STATIC
    YAML_CPP_STATIC_DEFINE
    _CRT_SECURE_NO_WARNINGS
    $<$<CONFIG:Debug>:_ITERATOR_DEBUG_LEVEL=2>  # Debug mode
    $<$<CONFIG:Release>:_ITERATOR_DEBUG_LEVEL=0> # Release mode
)

# Set runtime library to avoid mismatches (MD for Release, MDd for Debug)
target_compile_options(Editor PRIVATE 
    $<$<CONFIG:Debug>:/MDd>   # Debug mode: Multi-threaded Debug DLL
    $<$<CONFIG:Release>:/MD>   # Release mode: Multi-threaded DLL
)

# Link options
target_link_options(Editor PRIVATE /NODEFAULTLIB:LIBCMT)

# Platform-specific configuration
if(WIN32)
    target_precompile_headers(Editor PRIVATE "${CMAKE_SOURCE_DIR}/Engine/src/qbpch.h")
    target_compile_definitions(Editor PRIVATE QB_PLATFORM_WINDOWS GLFW_INCLUDE_NONE)

    target_link_directories(Editor PRIVATE 
        ${MSDF_ATLAS_GEN_DIR}
        $<$<CONFIG:Debug>:${GLFW_DIR}/build/src/Debug>
        $<$<CONFIG:Release>:${GLFW_DIR}/build/src/Release>
        $<$<CONFIG:Debug>:${ASSIMP_DIR}/build/lib/Debug>
        $<$<CONFIG:Release>:${ASSIMP_DIR}/build/lib/Release>
        $<$<CONFIG:Debug>:${ASSIMP_DIR}/build/contrib/zlib/Debug>
        $<$<CONFIG:Release>:${ASSIMP_DIR}/build/contrib/zlib/Release>
        $<$<CONFIG:Debug>:${GLEW_DIR}/Windows/lib/Release/x64>
        $<$<CONFIG:Release>:${GLEW_DIR}/Windows/lib/Release/x64>
        $<$<CONFIG:Release>:${MONO_DIR}/lib/Release>
        $<$<CONFIG:Debug>:${MONO_DIR}/lib/Debug>
        ${VULKAN_LIB_DIR}
    )

    target_link_libraries(Editor PRIVATE 
        opengl32 
        gdi32 
        winmm 
        Ws2_32 
        Winmm 
        Version 
        Bcrypt 
        skia.dll.lib
        freetype
        libpng16
        
        vulkan-1
        
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

        Engine 
        $<$<CONFIG:Debug>:msdfgen-cored>
        $<$<CONFIG:Release>:msdfgen-core>
        $<$<CONFIG:Debug>:msdfgen-extd>
        $<$<CONFIG:Release>:msdfgen-ext>
        $<$<CONFIG:Debug>:msdf-atlas-gend>
        $<$<CONFIG:Release>:msdf-atlas-gen>
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

# Enable Visual Studio folder support and show all files
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(TARGET Editor PROPERTY VS_SOLUTION_SHOW_ALL_FILES ON)

set_target_properties(Editor PROPERTIES
    VS_DEBUGGER_ENVIRONMENT "PATH=${CMAKE_SOURCE_DIR}/Editor/bin;$(PATH)"
)
