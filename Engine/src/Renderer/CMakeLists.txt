file(GLOB_RECURSE RENDERER_SOURCES "*.cpp" "*.cxx" "*.cc")

add_library(Renderer ${RENDERER_SOURCES})

target_include_directories(Renderer PUBLIC ../../../Vendor)
target_include_directories(Renderer PUBLIC ../../../Vendor/glfw/include)
target_include_directories(Renderer PUBLIC ../../../Vendor/imgui)
target_include_directories(Renderer PUBLIC ../../../Vendor/enTT/src/entt)
target_include_directories(Renderer PUBLIC ../../../Vendor/glm)
target_include_directories(Renderer PUBLIC ../../../Vendor/GLEW/include)

add_compile_definitions(GLEW_STATIC)

target_link_directories(Renderer 
PUBLIC ../../../Vendor/glfw/src/Debug 
PUBLIC ../../../Vendor/GLEW/lib/Release/x64
)

target_link_libraries(Renderer PUBLIC glfw glew32s gdi32 winmm opengl32)