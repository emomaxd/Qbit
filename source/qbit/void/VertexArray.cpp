#include "qbpch.h"
#include "Qbit/void/VertexArray.h"

#include "Qbit/void/Renderer.h"
#include "OpenGL/OpenGLVertexArray.h"
#include "Vulkan/VulkanVertexArray.h"

namespace Qbit {

	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    QB_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateRef<OpenGLVertexArray>();
		case RendererAPI::API::Vulkan:  return CreateRef<VulkanVertexArray>();
		}

		QB_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}