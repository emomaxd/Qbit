set(SRC 
    "stb_image.h"
    "stb_image.cpp"
)

add_library(stb-image STATIC "${SRC}")

target_include_directories(stb-image PUBLIC .)