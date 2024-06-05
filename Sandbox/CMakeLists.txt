project(Sandbox)

set(GLEW_DIR "${CMAKE_SOURCE_DIR}/Engine/vendor/glew")
set(GLFW_DIR "${CMAKE_SOURCE_DIR}/Engine/vendor/glfw")
set(IMGUI_DIR "${CMAKE_SOURCE_DIR}/Engine/vendor/imgui")
set(ENTT_DIR "${CMAKE_SOURCE_DIR}/Engine/vendor/entt")
set(GLM_DIR "${CMAKE_SOURCE_DIR}/Engine/vendor/glm")

file(GLOB_RECURSE SANDBOX_SOURCES "${CMAKE_SOURCE_DIR}/Sandbox/src/*.cpp")
file(GLOB_RECURSE SANDBOX_HEADERS "${CMAKE_SOURCE_DIR}/Sandbox/src/*.hpp")
file(GLOB_RECURSE SANDBOX_HEADERS "${CMAKE_SOURCE_DIR}/Sandbox/src/*.h")

add_library(Sandbox ${SANDBOX_SOURCES} ${SANDBOX_HEADERS})
#target_link_libraries(Sandbox PRIVATE Engine)
#target_include_directories(Sandbox PRIVATE ${CMAKE_SOURCE_DIR}/Engine/src)

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
    ${GLM_DIR}/glm
    ${ENTT_DIR}/src/entt
)

# Enable "Show All Files" option for Visual Studio projects
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(TARGET Sandbox PROPERTY VS_SOLUTION_SHOW_ALL_FILES ON)
