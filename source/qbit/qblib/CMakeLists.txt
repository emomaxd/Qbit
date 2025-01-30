set(CMAKE_CXX_STANDARD 17)


file(GLOB SRC
    "*.h"
    "*.cpp"
)

add_library(qblib STATIC ${SRC})

target_include_directories(qblib PUBLIC
    ..
    .
    ../core
)

target_link_libraries(qblib PUBLIC
    glm
)
