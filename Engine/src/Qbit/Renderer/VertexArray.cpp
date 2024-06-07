#include "qbpch.h"
#include "Qbit/Renderer/VertexArray.h"

#include "Qbit/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Qbit {

	Ref<VertexArray> VertexArray::Create()
	{
		//switch (Renderer::GetAPI())
		//{
		//case RendererAPI::API::None:    HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		//case RendererAPI::API::OpenGL:  
		return CreateRef<OpenGLVertexArray>();
		//}

		QB_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}