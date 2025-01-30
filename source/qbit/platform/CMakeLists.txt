set(CMAKE_CXX_STANDARD 17)

file(GLOB SRC
    "Windows/*.h"
    "Windows/*.cpp"
)

set(INC 
    ..
    .
)

set(LIB
    qblib
    core
    spdlog
    filewatch
    scene
    glfw
    window
    void
    event
)

add_library(platform STATIC ${SRC})

target_include_directories(platform PUBLIC ${INC})

target_link_libraries(platform PRIVATE ${LIB})