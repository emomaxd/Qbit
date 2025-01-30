#include "base.h"
#include "log.h"

#include "OpenGL/OpenGLContext.h"


#include <GL/glew.h>
#include <GLFW/glfw3.h>


namespace Qbit {

    OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
        : m_WindowHandle(windowHandle)
    {
        QB_CORE_ASSERT(windowHandle, "Window handle is null!")
    }

    void OpenGLContext::Init()
    {
        

        glfwMakeContextCurrent(m_WindowHandle);
        GLenum err = glewInit();
        QB_CORE_ASSERT(err == GLEW_OK, "Failed to initialize GLEW!");
        
        QB_CORE_INFO("OpenGL Info:");
        QB_CORE_INFO("  Vendor: {0}", (const char*)glGetString(GL_VENDOR));
        QB_CORE_INFO("  Renderer: {0}", (const char*)glGetString(GL_RENDERER));
        QB_CORE_INFO("  Version: {0}", (const char*)glGetString(GL_VERSION));

        QB_CORE_ASSERT(GLEW_VERSION_4_5, "Qbit requires at least OpenGL version 4.5!");
    }

    void OpenGLContext::SwapBuffers()
    {
        
        glfwSwapBuffers(m_WindowHandle);
    }

}
