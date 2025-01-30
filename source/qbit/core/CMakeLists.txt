set(CMAKE_CXX_STANDARD 17)

set(INC
    .
    ..
    ../scene
    ../qcs
    ../event
    ../utils
    ../window
    ../void
    ${CMAKE_SOURCE_DIR}/extern/entt/src/entt
    ${GLEW_INCLUDE_DIRS}
    ${VULKAN_INCLUDE_DIRS}
)

set(LIB
    entt
    glm
    glfw
    spdlog
    stb-image
    imgui
    imguizmo
    qblib
    window
    ${VULKAN_LIBS}
    ${GLEW_LIBS}
)

set(SRC
    application.h
    entry_point.h
    file_system.h
    imgui_layer.h
    input.h
    instrumentor.h
    key_codes.h
    layer.h
    layer_stack.h
    log.h
    mouse_codes.h
    timer.h
    timestep.h
    uuid.h

    application.cpp
    file_system.cpp
    imgui_build.cpp
    imgui_layer.cpp
    layer.cpp
    layer_stack.cpp
    log.cpp
    uuid.cpp
)

add_library(core STATIC ${SRC})
add_library(qbit::core ALIAS core)

target_include_directories(core PUBLIC ${INC})

target_link_libraries(core PRIVATE ${LIB})
