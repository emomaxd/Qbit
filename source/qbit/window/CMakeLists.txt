
file(GLOB SRC
    "*.h"
    "*.cpp"
)

add_library(window STATIC ${SRC})

target_include_directories(window PUBLIC
    ..
    .
    ../core
    ../event
)

target_link_libraries(window PRIVATE
    qblib
    void
    spdlog
    event
)
