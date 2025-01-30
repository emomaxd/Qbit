
set(CMAKE_CXX_STANDARD 17)

set(INC
    .
    ..
    ../..
    backend
    ${GLEW_INCLUDE_DIRS}
    ${VULKAN_INCLUDE_DIRS}
)

set(LIB
    core
    qblib
    event
    assimp
    glfw
    glm
    stb-image
    spdlog
    imgui
    msdf-atlas-gen
    ${GLEW_LIBS}
    ${VULKAN_LIBS}
)


file(GLOB SRC 
    "backend/*/*.h"
    "backend/*/*.cpp"
    "*.c"
    "*.cpp"
    "*.h"
    "*.hpp"
)

add_library(void STATIC "${SRC}")
add_library(qbit::void ALIAS void)

target_include_directories(void PUBLIC ${INC})

target_link_directories(void PUBLIC
    ${CMAKE_SOURCE_DIR}/lib
)

target_link_libraries(void PUBLIC

    ${LIB}
)

target_compile_definitions(void PUBLIC GLEW_STATIC)
