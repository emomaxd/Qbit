
set(CMAKE_CXX_STANDARD 17)

file(GLOB SRC 
    "src/*.c"
    "src/*.cpp"
    "src/*.h"
    "src/*.hpp"

    "src/*/*.c"
    "src/*/*.cpp"
    "src/*/*.h"
    "src/*/*.hpp"
)

add_executable(qbit "${SRC}")

target_include_directories(qbit PUBLIC
    ..
    ../qbit
    ${GLEW_INCLUDE_DIRS}
    ${VULKAN_INCLUDE_DIRS}
)

target_link_directories(qbit PUBLIC
    ${CMAKE_SOURCE_DIR}/lib
    ${CMAKE_CURRENT_BINARY_DIR}/../../lib/Debug
    ${CMAKE_CURRENT_BINARY_DIR}/../../lib/Release
)

target_link_libraries(qbit PUBLIC
  qblib
  core
  void
  platform
  project
  qcs
  window
  event
  scene
  stb-image
  glfw
  entt
  box2d
  assimp
  spdlog
  msdf-atlas-gen
  freetype
  glm
  yaml-cpp
  imgui
  imguizmo
  ${GLEW_LIBS}
  ${VULKAN_LIBS}
  ${MONO_LIBS}
  opengl32
  ws2_32
  bcrypt
  version
  winmm
  gdi32
)

target_compile_definitions(qbit PUBLIC GLEW_STATIC)

if(WIN32)
  target_compile_definitions(qbit PUBLIC QB_PLATFORM_WINDOWS)
endif()