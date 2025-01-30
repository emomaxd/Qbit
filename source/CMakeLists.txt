
# -----------------------------------------------------------------------------
# Compiler Warnings & Flags
# -----------------------------------------------------------------------------
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  #add_compile_options(-Wall -Wextra -pedantic -Werror -fno-rtti -fno-exceptions)
  # Performance optimizations for GCC/Clang
  #add_compile_options(-O3 -flto -march=native -funroll-loops -fomit-frame-pointer -ftree-vectorize)
elseif(MSVC)
  #add_compile_options(/W4 /WX /permissive-)
  # Performance optimizations for MSVC
  #add_compile_options(/GL /arch:AVX2 /fp:fast /favor:performance)
endif()

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(qbit)
add_subdirectory(creator)
