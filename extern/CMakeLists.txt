# Global definitions for static linking
set(YAML_CPP_BUILD_TESTS OFF)
set(YAML_CPP_BUILD_TOOLS OFF)
set(YAML_CPP_BUILD_CONTRIB OFF)
set(YAML_BUILD_SHARED_LIBS OFF)
set(SPDLOG_COMPILED_LIB ON)
set(BUILD_SHARED_LIBS OFF)

# Project-specific options
set(GLFW_BUILD_SHARED_LIBS OFF)
set(SPDLOG_BUILD_SHARED_LIBS OFF)

# Add subdirectories
add_subdirectory(assimp)
add_subdirectory(box2d)
add_subdirectory(entt)
add_subdirectory(filewatch)
add_subdirectory(glfw)
add_subdirectory(glm)
add_subdirectory(imgui)
add_subdirectory(imguizmo)
add_subdirectory(msdf-atlas-gen)
add_subdirectory(spdlog)
add_subdirectory(stb-image)
add_subdirectory(yaml-cpp)