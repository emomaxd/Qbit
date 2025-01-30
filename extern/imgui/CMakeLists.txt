
set(INC
    .
    ${VULKAN_INCLUDE_DIRS}
)

set(LIB
    glfw
    ${VULKAN_LIBS}
)

file(GLOB SRC
    "backends/*.h"
    "backends/*.cpp"
    "*.h"
    "*.cpp"
)

add_library(imgui STATIC ${SRC})
add_library(qbit::extern::imgui ALIAS imgui)

target_include_directories(imgui PUBLIC ${INC})

target_link_libraries(imgui PRIVATE ${LIB})
