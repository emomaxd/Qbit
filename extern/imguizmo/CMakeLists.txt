
set(INC
    .
)

set(LIB 
    imgui
)

file(GLOB SRC
    "*.h"
    "*.cpp"
)

add_library(imguizmo STATIC ${SRC})
add_library(qbit::extern::imguizmo ALIAS imguizmo)

target_include_directories(imguizmo PUBLIC ${INC})

target_link_libraries(imguizmo PRIVATE ${LIB})
