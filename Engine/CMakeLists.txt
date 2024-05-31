

# Define directories for third-party libraries
set(GLEW_DIR "vendor/glew")
set(GLFW_DIR "vendor/glfw")
set(IMGUI_DIR "vendor/imgui")
set(ENTT_DIR "vendor/entt")
set(GLM_DIR "vendor/glm")




file(GLOB SRC_FILES "src/Core/*.cpp"
                    "src/Renderer/*.cpp"
                    "src/Scene/*.cpp"
                    "src/System/*.cpp"

                    "src/Core/*.hpp"
                    "src/Renderer/*.hpp"
                    "src/Scene/*.hpp"
                    "src/System/*.hpp"

                    "${IMGUI_DIR}/*.cpp"
                    "${IMGUI_DIR}/backends/imgui_impl_glfw.cpp"
                    "${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp"
                    )



# Create Engine library
add_library(Engine 
    ${SRC_FILES}
)

# Include directories
target_include_directories(Engine PRIVATE 
    vendor
    ${GLFW_DIR}/install/include 
    ${GLEW_DIR}/include
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
    ${GLM_DIR}/glm
    ${ENTT_DIR}/src/entt
)

# Compile definitions
target_compile_definitions(Engine PRIVATE GLEW_STATIC)

# Link directories
if(WIN32)
    target_link_directories(Engine PRIVATE 
        ${GLFW_DIR}/install/lib
        ${GLEW_DIR}/Windows/lib/Release/x64
    )
elseif(UNIX)
    target_link_directories(Engine PRIVATE 
        ${GLFW_DIR}/install/lib 
        ${GLEW_DIR}/lib
    )
endif()

# Link libraries based on the operating system
if(WIN32)
    target_link_libraries(Engine PRIVATE 
        glew32s 
        glfw3 
        opengl32 
        gdi32 
        winmm
    )
elseif(UNIX)
    target_link_libraries(Engine PRIVATE 
        glfw3 
        GLEW 
        m 
        dl 
        pthread 
        GL
    )
else()
    message(FATAL_ERROR "Unsupported operating system")
endif()

# Set the output directory for the executable if needed
#set_target_properties(Engine PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/Out")

