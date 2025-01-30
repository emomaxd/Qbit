
file(GLOB_RECURSE SRC
    "*.h"
    "*.cpp"
)

add_library(entt INTERFACE ${SRC})