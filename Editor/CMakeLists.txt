project(Editor)

set(GLEW_DIR "${CMAKE_SOURCE_DIR}/Engine/vendor/glew")
set(GLFW_DIR "${CMAKE_SOURCE_DIR}/Engine/vendor/glfw")
set(IMGUI_DIR "${CMAKE_SOURCE_DIR}/Engine/vendor/imgui")
set(ENTT_DIR "${CMAKE_SOURCE_DIR}/Engine/vendor/entt")
set(GLM_DIR "${CMAKE_SOURCE_DIR}/Engine/vendor/glm")
set(ASSIMP_DIR "${CMAKE_SOURCE_DIR}/Engine/vendor/assimp")
set(IMGUIZMO_DIR "${CMAKE_SOURCE_DIR}/Engine/vendor/ImGuizmo")
set(MONO_DIR "${CMAKE_SOURCE_DIR}/Engine/vendor/mono")

file(GLOB_RECURSE CORE_SOURCES "*.cpp" "*.cxx" "*.cc" "*.hpp" "*.h")

add_executable(Editor ${CORE_SOURCES})

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
)

target_compile_definitions(Editor PRIVATE 
    $<$<CONFIG:Debug>:QB_DEBUG>
    $<$<CONFIG:Release>:QB_RELEASE>
    GLEW_STATIC
    YAML_CPP_STATIC_DEFINE
    _CRT_SECURE_NO_WARNINGS
)

target_link_options(Editor PRIVATE /NODEFAULTLIB:LIBCMT)

if(WIN32)
    target_precompile_headers(Editor PRIVATE "${CMAKE_SOURCE_DIR}/Engine/src/qbpch.h")
    target_compile_definitions(Editor PRIVATE QB_PLATFORM_WINDOWS GLFW_INCLUDE_NONE)

    target_link_directories(Editor PRIVATE 
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

    )

    target_link_libraries(Editor PRIVATE 
        opengl32 
        gdi32 
        winmm 
        Ws2_32 
        Winmm 
        Version 
        Bcrypt 
        Engine 

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

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(TARGET Editor PROPERTY VS_SOLUTION_SHOW_ALL_FILES ON)
