#include "qbpch.h"

#include "Qbit/Core/Application.h"

#include "VulkanContext.h"
#include "VulkanBuffer.h"

#include <vulkan/vulkan.h>



namespace Qbit {

	static uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties)
	{
		VulkanContext& context = (VulkanContext&)Application::Get().GetWindow().GetGraphicsContext();
		VkPhysicalDevice physicalDevice = context.GetPhysicalDevice();

		VkPhysicalDeviceMemoryProperties memProperties;
		vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memProperties);

		for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++)
		{
			if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
				return i;
			}
		}

		QB_CORE_ERROR("Failed to find suitable memory type!");
		QB_CORE_ASSERT(false);
	}

	VulkanVertexBuffer::VulkanVertexBuffer(uint32_t size)
	{
		/*
		// Create a memory region in amount size with NULL data.
		*/

		
		{
			VulkanContext& context = (VulkanContext&)Application::Get().GetWindow().GetGraphicsContext();
			m_Device = context.GetDevice();
		}


		VkBufferCreateInfo bufferInfo{};
		bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		bufferInfo.size = size;
		bufferInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
		bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

		if (vkCreateBuffer(m_Device, &bufferInfo, nullptr, &m_VertexBuffer) != VK_SUCCESS)
		{
			QB_CORE_ERROR("Failed to create vertex buffer!");
			QB_CORE_ASSERT(false);
		}

		// Buffer has been created but it does not have any memory region.
		// So we MUST create a memory region for our buffer.

		VkMemoryRequirements memRequirements; // size, alignment, memoryTypeBits
		vkGetBufferMemoryRequirements(m_Device, m_VertexBuffer, &memRequirements);
		
		VkMemoryAllocateInfo allocInfo{}; 
		allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		allocInfo.allocationSize = memRequirements.size;
		allocInfo.memoryTypeIndex = findMemoryType(memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

		if (vkAllocateMemory(m_Device, &allocInfo, nullptr, &m_VertexBufferMemory) != VK_SUCCESS)
		{
			QB_CORE_ERROR("Failed to allocate vertex buffer memory!");
			QB_CORE_ASSERT(false);
		}

		vkBindBufferMemory(m_Device, m_VertexBuffer, m_VertexBufferMemory, 0);

		/*
		// Mapping the memory is unnecessary for this function, since we only have size don't have any data.
		// Mapping is used when we want to copy data from CPU to GPU.
		*/

		//void* data;
		//vkMapMemory(m_Device, m_VertexBufferMemory, 0, bufferInfo.size, 0, &data);
		// memcpy(data, vertices.data(), (size_t)bufferInfo.size);
		//vkUnmapMemory(m_Device, m_VertexBufferMemory);
	}

	VulkanVertexBuffer::VulkanVertexBuffer(float* vertices, uint32_t size)
	{
		{
			VulkanContext& context = (VulkanContext&)Application::Get().GetWindow().GetGraphicsContext();
			m_Device = context.GetDevice();
		}


		VkBufferCreateInfo bufferInfo{};
		bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		bufferInfo.size = size;
		bufferInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
		bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

		if (vkCreateBuffer(m_Device, &bufferInfo, nullptr, &m_VertexBuffer) != VK_SUCCESS)
		{
			QB_CORE_ERROR("Failed to create vertex buffer!");
			QB_CORE_ASSERT(false);
		}

		// Buffer has been created but it does not have any memory region.
		// So we MUST create a memory region for our buffer.

		VkMemoryRequirements memRequirements; // size, alignment, memoryTypeBits
		vkGetBufferMemoryRequirements(m_Device, m_VertexBuffer, &memRequirements);

		VkMemoryAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		allocInfo.allocationSize = memRequirements.size;
		allocInfo.memoryTypeIndex = findMemoryType(memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

		if (vkAllocateMemory(m_Device, &allocInfo, nullptr, &m_VertexBufferMemory) != VK_SUCCESS)
		{
			QB_CORE_ERROR("Failed to allocate vertex buffer memory!");
			QB_CORE_ASSERT(false);
		}

		vkBindBufferMemory(m_Device, m_VertexBuffer, m_VertexBufferMemory, 0);

		void* data;
		vkMapMemory(m_Device, m_VertexBufferMemory, 0, bufferInfo.size, 0, &data);
		memcpy(data, vertices, (size_t)bufferInfo.size);
		vkUnmapMemory(m_Device, m_VertexBufferMemory);
	}

	VulkanVertexBuffer::~VulkanVertexBuffer()
	{
		vkDestroyBuffer(m_Device, m_VertexBuffer, nullptr);
		vkFreeMemory(m_Device, m_VertexBufferMemory, nullptr);
	}

	void VulkanVertexBuffer::Bind() const
	{
		// No specific bind function in vulkan.
	}

	void VulkanVertexBuffer::Unbind() const
	{
		// No specific unbind function in vulkan.
	}

	void VulkanVertexBuffer::SetData(const void* data, uint32_t size)
	{
		/*
		// NO TESTING HAS BEEN DONE!
		*/

		void* mapped_data;
		vkMapMemory(m_Device, m_VertexBufferMemory, 0, size, 0, &mapped_data);
		memcpy(mapped_data, data, size);
		vkUnmapMemory(m_Device, m_VertexBufferMemory);
	}

}