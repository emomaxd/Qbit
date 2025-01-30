set(CMAKE_CXX_STANDARD 17)

file(GLOB SRC
    "*.h"
    "*.cpp"
)

add_library(scene STATIC ${SRC})

target_include_directories(scene PUBLIC
    ..
    .
    ${CMAKE_SOURCE_DIR}/extern/yaml-cpp/include
    ${CMAKE_SOURCE_DIR}/extern/box2d/include
    ${CMAKE_SOURCE_DIR}/extern/entt/src/entt
)

target_link_libraries(scene PUBLIC
    qblib
    core
    spdlog
    box2d
    yaml-cpp
    entt
    void
)