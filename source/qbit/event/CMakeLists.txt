
file(GLOB SRC
    "*.h"
    "*.cpp"
)

add_library(event STATIC ${SRC})

target_include_directories(event PUBLIC
    .
)

target_link_libraries(event PRIVATE
    core
    qblib
    spdlog
)