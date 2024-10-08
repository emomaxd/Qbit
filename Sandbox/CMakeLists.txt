project(Sandbox)

set(GLEW_DIR "${CMAKE_SOURCE_DIR}/Engine/vendor/glew")
set(GLFW_DIR "${CMAKE_SOURCE_DIR}/Engine/vendor/glfw")
set(IMGUI_DIR "${CMAKE_SOURCE_DIR}/Engine/vendor/imgui")
set(ENTT_DIR "${CMAKE_SOURCE_DIR}/Engine/vendor/entt")
set(GLM_DIR "${CMAKE_SOURCE_DIR}/Engine/vendor/glm")
set(ASSIMP_DIR "${CMAKE_SOURCE_DIR}/Engine/vendor/assimp")
set(MONO_DIR "${CMAKE_SOURCE_DIR}/Engine/vendor/mono")

file(GLOB_RECURSE SANDBOX_SOURCES "${CMAKE_SOURCE_DIR}/Sandbox/src/*.cpp")
file(GLOB_RECURSE SANDBOX_HEADERS "${CMAKE_SOURCE_DIR}/Sandbox/src/*.hpp" "${CMAKE_SOURCE_DIR}/Sandbox/src/*.h")

add_executable(Sandbox ${SANDBOX_SOURCES} ${SANDBOX_HEADERS})

target_include_directories(Sandbox PRIVATE 
    ${CMAKE_SOURCE_DIR}/Engine
    ${CMAKE_SOURCE_DIR}/Engine/src
    ${CMAKE_SOURCE_DIR}/Engine/vendor
    ${CMAKE_SOURCE_DIR}/Engine/vendor/spdlog/include
    ${GLFW_DIR}/include 
    ${GLEW_DIR}/include
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
    ${GLM_DIR}
    ${GLM_DIR}/glm
    ${ENTT_DIR}/src/entt
    ${ASSIMP_DIR}/include
    ${MONO_DIR}/include
)

target_compile_definitions(Sandbox PRIVATE 
    $<$<CONFIG:Debug>:QB_DEBUG>
    $<$<CONFIG:Release>:QB_RELEASE>
    GLEW_STATIC
    YAML_CPP_STATIC_DEFINE
    _CRT_SECURE_NO_WARNINGS
)

if(WIN32)
    target_precompile_headers(Sandbox PRIVATE "${CMAKE_SOURCE_DIR}/Engine/src/qbpch.h")
    target_compile_definitions(Sandbox PRIVATE QB_PLATFORM_WINDOWS GLFW_INCLUDE_NONE)

    target_link_directories(Sandbox PRIVATE 
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

    target_link_libraries(Sandbox PRIVATE 
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
set_property(TARGET Sandbox PROPERTY VS_SOLUTION_SHOW_ALL_FILES ON)
