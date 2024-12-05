#include "qbpch.h"
#include "Qbit/Renderer/RendererAPI.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"
#include "Platform/Vulkan/VulkanRendererAPI.h"


namespace Qbit {

	//RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;
	RendererAPI::API RendererAPI::s_API = RendererAPI::API::Vulkan;

	Scope<RendererAPI> RendererAPI::Create()
	{
		switch (s_API)
		{
		case RendererAPI::API::None:    QB_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateScope<OpenGLRendererAPI>();
		case RendererAPI::API::Vulkan:  return CreateScope<VulkanRendererAPI>();
		}

		QB_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}