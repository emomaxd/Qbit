file(GLOB_RECURSE CORE_SOURCES "*.cpp" "*.cxx" "*.cc")

add_library(Core ${CORE_SOURCES})

target_include_directories(Core PUBLIC ../../../Vendor)
target_include_directories(Core PUBLIC ../../../Vendor/glfw/include)
target_include_directories(Core PUBLIC ../../../Vendor/imgui)
target_include_directories(Core PUBLIC ../../../Vendor/enTT/src/entt)
target_include_directories(Core PUBLIC ../../../Vendor/glm)
target_include_directories(Core PUBLIC ../../../Vendor/GLEW/include)

add_compile_definitions(GLEW_STATIC)

target_link_directories(Core 
PUBLIC ../../../Vendor/glfw/src/Debug 
PUBLIC ../../../Vendor/GLEW/lib/Release/x64
)

target_link_libraries(Core PUBLIC glfw glew32s gdi32 winmm opengl32)