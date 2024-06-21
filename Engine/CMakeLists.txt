# Define directories for third-party libraries
set(GLEW_DIR "${CMAKE_SOURCE_DIR}/Engine/vendor/glew")
set(GLFW_DIR "${CMAKE_SOURCE_DIR}/Engine/vendor/glfw")
set(IMGUI_DIR "${CMAKE_SOURCE_DIR}/Engine/vendor/imgui")
set(ENTT_DIR "${CMAKE_SOURCE_DIR}/Engine/vendor/entt")
set(GLM_DIR "${CMAKE_SOURCE_DIR}/Engine/vendor/glm")
set(ASSIMP_DIR "${CMAKE_SOURCE_DIR}/Engine/vendor/assimp")

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


# Create Engine library
add_library(Engine 
    ${ENGINE_SRC}
    ${IMGUI_SRC}
)

# Include directories
target_include_directories(Engine PRIVATE 
    ${CMAKE_SOURCE_DIR}/Engine
    ${CMAKE_SOURCE_DIR}/Engine/src
    ${CMAKE_SOURCE_DIR}/Engine/vendor
    ${CMAKE_SOURCE_DIR}/Engine/vendor/spdlog/include
    ${GLFW_DIR}/install/include 
    ${GLEW_DIR}/include
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
    ${GLM_DIR}/glm
    ${GLM_DIR}
    ${ENTT_DIR}/src/entt
    ${ASSIMP_DIR}/include
)

# Compile definitions
target_compile_definitions(Engine PRIVATE GLEW_STATIC)

# Define QB_DEBUG for Debug configuration only
target_compile_definitions(Engine PRIVATE 
    $<$<CONFIG:Debug>:QB_DEBUG>
    _CRT_SECURE_NO_WARNINGS
)

# Link libraries based on the operating system
if(WIN32)
    target_precompile_headers(Engine PRIVATE "${CMAKE_SOURCE_DIR}/Engine/src/qbpch.h")
    target_compile_definitions(Engine PRIVATE QB_PLATFORM_WINDOWS GLFW_INCLUDE_NONE)

    

    target_link_directories(Engine PRIVATE 
        ${GLFW_DIR}/install/lib
        ${GLEW_DIR}/Windows/lib/Release/x64
        ${ASSIMP_DIR}/lib/Debug/
        ${ASSIMP_DIR}/contrib/zlib/Release
    )
    target_link_libraries(Engine PRIVATE 
        glew32s 
        glfw3 
        opengl32 
        gdi32 
        winmm
        assimp-vc143-mtd
        zlibstatic
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
