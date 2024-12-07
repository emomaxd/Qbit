#include "qbpch.h"

#include "Platform/Vulkan/VulkanRendererAPI.h"
#include "Platform/Vulkan/VulkanContext.h"

#include "Qbit/Core/Application.h"

namespace Qbit {

	void VulkanRendererAPI::Init()
	{
		QB_PROFILE_FUNCTION();

#ifdef QB_DEBUG
		
#endif


	}

	void VulkanRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		VulkanContext& context = (VulkanContext&)Application::Get().GetWindow().GetGraphicsContext();
		context.SetResized(true);
	}

	void VulkanRendererAPI::SetClearColor(const glm::vec4& color)
	{
	}

	void VulkanRendererAPI::Clear()
	{
	}

	void VulkanRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount)
	{
		vertexArray->Bind();
		uint32_t count = indexCount ? indexCount : vertexArray->GetIndexBuffer()->GetCount();
		// Draw call
	}

	void VulkanRendererAPI::DrawLines(const Ref<VertexArray>& vertexArray, uint32_t vertexCount)
	{
		vertexArray->Bind();
		// Draw call
	}

	void VulkanRendererAPI::SetLineWidth(float width)
	{
	}

}