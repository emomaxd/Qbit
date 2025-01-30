set(CMAKE_CXX_STANDARD 17)

file(GLOB SRC
    "*.h"
    "*.cpp"
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
)

add_library(project STATIC ${SRC})

target_include_directories(project PUBLIC ${INC})

target_link_libraries(project PRIVATE ${LIB})