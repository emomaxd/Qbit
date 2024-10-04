project(Editor)

set(GLEW_DIR "${CMAKE_SOURCE_DIR}/Engine/vendor/glew")
set(GLFW_DIR "${CMAKE_SOURCE_DIR}/Engine/vendor/glfw")
set(IMGUI_DIR "${CMAKE_SOURCE_DIR}/Engine/vendor/imgui")
set(ENTT_DIR "${CMAKE_SOURCE_DIR}/Engine/vendor/entt")
set(GLM_DIR "${CMAKE_SOURCE_DIR}/Engine/vendor/glm")
set(ASSIMP_DIR "${CMAKE_SOURCE_DIR}/Engine/vendor/assimp")
set(IMGUIZMO_DIR "${CMAKE_SOURCE_DIR}/Engine/vendor/ImGuizmo")
set(MONO_DIR "${CMAKE_SOURCE_DIR}/Engine/vendor/mono")



# Include subdirectories
file(GLOB_RECURSE CORE_SOURCES "*.cpp" "*.cxx" "*.cc" "*.hpp" ".h")

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
    ${IMGUIZMO_DIR}
    ${MONO_DIR}/include
)

if(WIN32)
    target_precompile_headers(Editor PRIVATE "${CMAKE_SOURCE_DIR}/Engine/src/qbpch.h")
    target_compile_definitions(Editor PRIVATE QB_PLATFORM_WINDOWS GLFW_INCLUDE_NONE)

    

    target_link_directories(Editor PRIVATE 
        ${GLFW_DIR}/install/lib
        ${GLEW_DIR}/Windows/lib/Release/x64
        ${ASSIMP_DIR}/lib/Debug/
        ${ASSIMP_DIR}/contrib/zlib/Debug
        ${MONO_DIR}/lib/Release

    )
    target_link_libraries(Editor PRIVATE 
        glew32s 
        glfw3 
        opengl32 
        gdi32 
        winmm
        assimp-vc143-mtd
        zlibstaticd
        libmono-static-sgen
        Ws2_32
        Winmm
        Version
        Bcrypt
        Engine
    )
elseif(UNIX)
    target_link_directories(Editor PRIVATE 
        ${GLFW_DIR}/install/lib 
        ${GLEW_DIR}/lib
    )
    target_link_libraries(Editor PRIVATE 
        glfw3 
        GLEW 
        m 
        dl 
        pthread 
        GL
        Engine
    )
else()
    message(FATAL_ERROR "Unsupported operating system")
endif()

# Enable "Show All Files" option for Visual Studio projects
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(TARGET Editor PROPERTY VS_SOLUTION_SHOW_ALL_FILES ON)
