project(Sandbox)

set(GLEW_DIR "${CMAKE_SOURCE_DIR}/Engine/vendor/glew")
set(GLFW_DIR "${CMAKE_SOURCE_DIR}/Engine/vendor/glfw")
set(IMGUI_DIR "${CMAKE_SOURCE_DIR}/Engine/vendor/imgui")
set(ENTT_DIR "${CMAKE_SOURCE_DIR}/Engine/vendor/entt")
set(GLM_DIR "${CMAKE_SOURCE_DIR}/Engine/vendor/glm")
set(ASSIMP_DIR "${CMAKE_SOURCE_DIR}/Engine/vendor/assimp")


file(GLOB_RECURSE SANDBOX_SOURCES "${CMAKE_SOURCE_DIR}/Sandbox/src/*.cpp")
file(GLOB_RECURSE SANDBOX_HEADERS "${CMAKE_SOURCE_DIR}/Sandbox/src/*.hpp")
file(GLOB_RECURSE SANDBOX_HEADERS "${CMAKE_SOURCE_DIR}/Sandbox/src/*.h")

add_executable(Sandbox ${SANDBOX_SOURCES} ${SANDBOX_HEADERS})

# Include directories
target_include_directories(Sandbox PRIVATE 
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
)

if(WIN32)
    target_precompile_headers(Sandbox PRIVATE "${CMAKE_SOURCE_DIR}/Engine/src/qbpch.h")
    target_compile_definitions(Sandbox PRIVATE QB_PLATFORM_WINDOWS GLFW_INCLUDE_NONE)

    

    target_link_directories(Sandbox PRIVATE 
        ${GLFW_DIR}/install/lib
        ${GLEW_DIR}/Windows/lib/Release/x64
        ${ASSIMP_DIR}/lib/Debug/
        ${ASSIMP_DIR}/contrib/zlib/Release
    )
    target_link_libraries(Sandbox PRIVATE 
        glew32s 
        glfw3 
        opengl32 
        gdi32 
        winmm
        assimp-vc143-mtd
        zlibstatic
        Engine
    )
elseif(UNIX)
    target_link_directories(Sandbox PRIVATE 
        ${GLFW_DIR}/install/lib 
        ${GLEW_DIR}/lib
    )
    target_link_libraries(Sandbox PRIVATE 
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
set_property(TARGET Sandbox PROPERTY VS_SOLUTION_SHOW_ALL_FILES ON)
