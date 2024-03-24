cmake_minimum_required(VERSION 3.0)

# Project name
project(ImGuiLibrary)

# Collect all source files
file(GLOB IMGUI_SRC_FILES "*.cpp")

# Create library target
add_library(ImGui ${IMGUI_SRC_FILES})

target_include_directories(ImGui PUBLIC ../glfw/include)
target_include_directories(ImGui PUBLIC ../enTT/src/entt)
target_include_directories(ImGui PUBLIC ../glm)
target_include_directories(ImGui PUBLIC ../GLEW/include)