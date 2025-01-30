set(GLEW_INCLUDE_DIRS "${QBIT_LIB_DIR}/glew/include" CACHE INTERNAL "GLEW include dirs")
set(GLEW_LIBS "${QBIT_LIB_DIR}/glew/lib/glew32s.lib" CACHE INTERNAL "GLEW libraries")

# Vulkan libraries
set(VULKAN_INCLUDE_DIRS "${QBIT_LIB_DIR}/vulkan/include" CACHE INTERNAL "Vulkan include dirs")

set(VULKAN_LIBS
    "${QBIT_LIB_DIR}/vulkan/lib/vulkan-1.lib"
    "${QBIT_LIB_DIR}/vulkan/lib/$<$<CONFIG:Debug>:glslangd>$<$<CONFIG:Release>:glslang>.lib"
    "${QBIT_LIB_DIR}/vulkan/lib/$<$<CONFIG:Debug>:shaderc_utild>$<$<CONFIG:Release>:shaderc_util>.lib"
    "${QBIT_LIB_DIR}/vulkan/lib/$<$<CONFIG:Debug>:shadercd>$<$<CONFIG:Release>:shaderc>.lib"
    "${QBIT_LIB_DIR}/vulkan/lib/$<$<CONFIG:Debug>:spirv-cross-cored>$<$<CONFIG:Release>:spirv-cross-core>.lib"
    "${QBIT_LIB_DIR}/vulkan/lib/$<$<CONFIG:Debug>:spirv-cross-glsld>$<$<CONFIG:Release>:spirv-cross-glsl>.lib"
    "${QBIT_LIB_DIR}/vulkan/lib/$<$<CONFIG:Debug>:spirv-cross-utild>$<$<CONFIG:Release>:spirv-cross-util>.lib"
    "${QBIT_LIB_DIR}/vulkan/lib/$<$<CONFIG:Debug>:SPIRV-Toolsd>$<$<CONFIG:Release>:SPIRV-Tools>.lib"
    "${QBIT_LIB_DIR}/vulkan/lib/$<$<CONFIG:Debug>:SPIRV-Tools-optd>$<$<CONFIG:Release>:SPIRV-Tools-opt>.lib"
    "${QBIT_LIB_DIR}/vulkan/lib/$<$<CONFIG:Debug>:SPIRVd>$<$<CONFIG:Release>:SPIRV>.lib"
    CACHE INTERNAL "Vulkan libraries")


# Mono libraries (no change)
set(MONO_INCLUDE_DIRS "${QBIT_LIB_DIR}/mono/include" CACHE INTERNAL "Mono include dirs")
set(MONO_LIBS "${QBIT_LIB_DIR}/mono/lib/Release/libmono-static-sgen.lib" CACHE INTERNAL "Mono libraries")

