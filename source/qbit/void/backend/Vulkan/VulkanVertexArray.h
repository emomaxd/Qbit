/*************************************************************************/
/**
 * @file VulkanVertexArray.h
 * @brief Vulkan-specific implementation of a vertex array.
 *
 * @details
 * This class implements the `VertexArray` interface for Vulkan, managing
 * vertex buffers and an index buffer. It abstracts Vulkan's explicit
 * buffer management, simulating the behavior of Qbit's API-agnostic Vertex Array
 * Objects (VAOs). The class handles Vulkan-specific setup for binding
 * buffers and pipeline configuration.
 *  
 * @section Author
 * emomaxd
 * Created on:		2025-01-17
 * Last Updated on: 2025-01-17
 **************************************************************************/


#pragma once

#include "Qbit/void/VertexArray.h"

#include <vulkan/vulkan.h>

#include "base.h"

namespace Qbit {

	class VulkanVertexArray : public VertexArray
	{
	public:
		VulkanVertexArray();
		virtual ~VulkanVertexArray();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;

		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const { return m_VertexBuffers; }
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }

		const std::vector<VkVertexInputBindingDescription>& GetBindingDescriptions() { return m_BindingDescriptions; }
		const std::vector<VkVertexInputAttributeDescription>& GetAttributeDescriptions() { return m_AttributeDescriptions; }

	private:
		uint32_t m_VertexBufferIndex = 0;
		std::vector<Ref<VertexBuffer>> m_VertexBuffers;
		Ref<IndexBuffer> m_IndexBuffer;

		std::vector<VkVertexInputBindingDescription> m_BindingDescriptions;
		std::vector<VkVertexInputAttributeDescription> m_AttributeDescriptions;
	};

}