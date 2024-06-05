# Include subdirectories
file(GLOB_RECURSE CORE_SOURCES "*.cpp" "*.cxx" "*.cc" "*.hpp" ".h")

add_library(Editor ${CORE_SOURCES})

#target_include_directories(Editor PUBLIC ../Vendor)
#target_include_directories(Editor PUBLIC ../Vendor/glfw/include)
#target_include_directories(Editor PUBLIC ../Vendor/imgui)
#target_include_directories(Editor PUBLIC ../Vendor/enTT/src/entt)
#target_include_directories(Editor PUBLIC ../Vendor/glm)
#target_include_directories(Editor PUBLIC ../Vendor/GLEW/include)

#add_compile_definitions(GLEW_STATIC)

#target_link_directories(Editor 
#PUBLIC ../Vendor/glfw/src/Debug 
#PUBLIC ../Vendor/GLEW/lib/Release/x64
#)

#target_link_libraries(Editor PUBLIC glfw glew32s gdi32 winmm opengl32)

# Enable "Show All Files" option for Visual Studio projects
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(TARGET Editor PROPERTY VS_SOLUTION_SHOW_ALL_FILES ON)
