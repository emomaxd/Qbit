set(SRC 
    "FileWatch.h"
    "main.cpp"
)

add_library(filewatch STATIC "${SRC}")

target_include_directories(filewatch PUBLIC
    .
)