project(Sandbox)

set(GLEW_DIR "${CMAKE_SOURCE_DIR}/Engine/vendor/glew")
set(GLFW_DIR "${CMAKE_SOURCE_DIR}/Engine/vendor/glfw")
set(IMGUI_DIR "${CMAKE_SOURCE_DIR}/Engine/vendor/imgui")
set(ENTT_DIR "${CMAKE_SOURCE_DIR}/Engine/vendor/entt")
set(GLM_DIR "${CMAKE_SOURCE_DIR}/Engine/vendor/glm")

file(GLOB_RECURSE SANDBOX_SOURCES "${CMAKE_SOURCE_DIR}/Sandbox/src/*.cpp")
file(GLOB_RECURSE SANDBOX_HEADERS "${CMAKE_SOURCE_DIR}/Sandbox/src/*.hpp")

add_library(Sandbox ${SANDBOX_SOURCES} ${SANDBOX_HEADERS})
#target_link_libraries(Sandbox PRIVATE Engine)
#target_include_directories(Sandbox PRIVATE ${CMAKE_SOURCE_DIR}/Engine/src)

target_include_directories(Sandbox PRIVATE
    ${CMAKE_SOURCE_DIR}/Engine/src
    ${CMAKE_SOURCE_DIR}/Engine/vendor
    ${GLFW_DIR}/install/include 
    ${GLEW_DIR}/include
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
    ${GLM_DIR}/glm
    ${ENTT_DIR}/src/entt
)
