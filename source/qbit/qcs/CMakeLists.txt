set(CMAKE_CXX_STANDARD 17)

file(GLOB SRC
    "*.h"
    "*.cpp"
)

set(INC 
    ..
    .
    ${CMAKE_SOURCE_DIR}/extern/box2d/include
    ${MONO_INCLUDE_DIRS}
)

set(LIB
    qblib
    core
    spdlog
    glm
    entt
    box2d
    filewatch
    project
    void
    scene
    ${MONO_LIBS}
)

add_library(qcs STATIC ${SRC})

target_include_directories(qcs PUBLIC ${INC})

target_link_libraries(qcs PRIVATE ${LIB})