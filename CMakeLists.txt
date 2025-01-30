# ============================
# CMake Version and Initial Setup
# ============================
cmake_minimum_required(VERSION 3.10)

# Prevent in-source builds (stay out of the source directory)
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR} AND NOT DEFINED WITH_IN_SOURCE_BUILD)
  message(FATAL_ERROR
    "CMake generation for Qbit is not allowed within the source directory!"
    "\nRemove the CMakeCache.txt and CMakeFiles directories and build out-of-source."
    "\nExample:"
    "\n mkdir build && cd build && cmake .."
  )
endif()

# ============================
# Project Initialization
# ============================
project(Qbit)

# Enable testing
enable_testing()

# Set default CMake build type if not defined
if(NOT DEFINED CMAKE_BUILD_TYPE_INIT)
  set(CMAKE_BUILD_TYPE_INIT "Release")
endif()
mark_as_advanced(CMAKE_BUILD_TYPE_INIT)

# Set compile definitions based on the build configuration
set_property(DIRECTORY APPEND PROPERTY COMPILE_DEFINITIONS
  $<$<CONFIG:Debug>:QB_DEBUG>
)

# -----------------------------------------------------------------------------
# Set Platform-Specific Defines
# -----------------------------------------------------------------------------
if(WIN32)
  add_definitions(-DQB_PLATFORM_WINDOWS)
elseif(APPLE)
  add_definitions(-DQB_PLATFORM_MACOS)
elseif(UNIX)
  add_definitions(-DQB_PLATFORM_LINUX)
endif()

# -----------------------------------------------------------------------------
# Export Compile Commands (for VSCode, etc.)
# -----------------------------------------------------------------------------
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
# -----------------------------------------------------------------------------

# ============================
# Compiler Support Check (GCC, Clang, MSVC)
# ============================
if(CMAKE_COMPILER_IS_GNUCC)
  if("${CMAKE_C_COMPILER_VERSION}" VERSION_LESS "11.0.0")
    message(FATAL_ERROR "The minimum supported version of GCC is 11.0.0, found C compiler: ${CMAKE_C_COMPILER_VERSION}")
  endif()
  if("${CMAKE_CXX_COMPILER_VERSION}" VERSION_LESS "11.0.0")
    message(FATAL_ERROR "The minimum supported version of GCC is 11.0.0, found C++ compiler: ${CMAKE_CXX_COMPILER_VERSION}")
  endif()
elseif(CMAKE_C_COMPILER_ID MATCHES "Clang")
  if("${CMAKE_C_COMPILER_VERSION}" VERSION_LESS "8.0")
    message(FATAL_ERROR "The minimum supported version of CLANG is 8.0, found C compiler: ${CMAKE_C_COMPILER_VERSION}")
  endif()
  if("${CMAKE_CXX_COMPILER_VERSION}" VERSION_LESS "8.0")
    message(FATAL_ERROR "The minimum supported version of CLANG is 8.0, found C++ compiler: ${CMAKE_CXX_COMPILER_VERSION}")
  endif()
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  if(MSVC_VERSION VERSION_LESS "1928")
    message(FATAL_ERROR "The minimum supported version of MSVC is 2019 (16.9.16)")
  endif()
endif()

# ============================
# Versioning
# ============================
set(QBIT_VERSION_MAJOR 0)
set(QBIT_VERSION_MINOR 3)

# ============================
# Platform-Specific Definitions (Windows)
# ============================
if(WIN32)
  add_definitions(
    -DQBIT_WIN_APPID="qbit.${QBIT_VERSION_MAJOR}.${QBIT_VERSION_MINOR}"
    -DQBIT_WIN_APPID_FRIENDLY_NAME="QBit ${QBIT_VERSION_MAJOR}.${QBIT_VERSION_MINOR}"
  )
endif()

# -----------------------------------------------------------------------------
# Set up Installation Directories
# -----------------------------------------------------------------------------
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)



#------------------------------------------------------------------------------
# Setup include and lib dirs
#------------------------------------------------------------------------------
set(QBIT_EXTERNAL_DIR ${CMAKE_SOURCE_DIR}/extern)
set(QBIT_LIB_DIR ${CMAKE_SOURCE_DIR}/lib)


if(WIN32)
    set(QBIT_LIB_DIR "${QBIT_LIB_DIR}/windows_x64")
elseif(UNIX)
    set(QBIT_LIB_DIR "${QBIT_LIB_DIR}/linux_x64")
endif()

set(QBIT_LIB_DIR "${QBIT_LIB_DIR}" CACHE PATH "Platform-specific library directory")


# ============================
# CMake Module Path and Functions
# ============================
include(${CMAKE_SOURCE_DIR}/build_files/cmake/macros.cmake)
include(${CMAKE_SOURCE_DIR}/build_files/cmake/libs.cmake)

# ============================
# Adding Source and External Subdirectories
# ============================
add_subdirectory(source)

# -----------------------------------------------------------------------------
# External Subdirectory Handling
# -----------------------------------------------------------------------------
add_subdirectory(extern)


install(TARGETS qbit DESTINATION ${CMAKE_BINARY_DIR}/bin)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/source/creator/assets DESTINATION ${CMAKE_BINARY_DIR}/bin)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/source/creator/mono DESTINATION ${CMAKE_BINARY_DIR}/bin)

# ============================
# End of CMake Configuration
# ============================
