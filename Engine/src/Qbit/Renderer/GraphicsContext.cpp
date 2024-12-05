#include "qbpch.h"
#include "Qbit/Renderer/GraphicsContext.h"

#include "Qbit/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLContext.h"
#include "Platform/Vulkan/VulkanContext.h"


namespace Qbit {

	Scope<GraphicsContext> GraphicsContext::Create(void* window)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    QB_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
		case RendererAPI::API::Vulkan:  return CreateScope<VulkanContext>(static_cast<GLFWwindow*>(window));
		}

		return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));

		QB_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}