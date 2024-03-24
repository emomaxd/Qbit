file(GLOB_RECURSE SCENE_SOURCES "*.cpp" "*.cxx" "*.cc")

add_library(Scene ${SCENE_SOURCES})

target_include_directories(Scene PUBLIC ../../../Vendor)
target_include_directories(Scene PUBLIC ../../../Vendor/glfw/include)
target_include_directories(Scene PUBLIC ../../../Vendor/imgui)
target_include_directories(Scene PUBLIC ../../../Vendor/enTT/src/entt)
target_include_directories(Scene PUBLIC ../../../Vendor/glm)
target_include_directories(Scene PUBLIC ../../../Vendor/GLEW/include)

add_compile_definitions(GLEW_STATIC)

target_link_directories(Scene 
PUBLIC ../../../Vendor/glfw/src/Debug 
PUBLIC ../../../Vendor/GLEW/lib/Release/x64
)

target_link_libraries(Scene PUBLIC glfw glew32s gdi32 winmm opengl32)