#include "VulkanVertexArray.h"

#include "base.h"

namespace Qbit {

    namespace Util {
        // Utility to convert ShaderDataType to Vulkan format
        VkFormat ShaderDataTypeToVulkanFormat(ShaderDataType type)
        {
            switch (type)
            {
            case ShaderDataType::Float:   return VK_FORMAT_R32_SFLOAT;
            case ShaderDataType::Float2:  return VK_FORMAT_R32G32_SFLOAT;
            case ShaderDataType::Float3:  return VK_FORMAT_R32G32B32_SFLOAT;
            case ShaderDataType::Float4:  return VK_FORMAT_R32G32B32A32_SFLOAT;
            case ShaderDataType::Int:     return VK_FORMAT_R32_SINT;
            case ShaderDataType::Int2:    return VK_FORMAT_R32G32_SINT;
            case ShaderDataType::Int3:    return VK_FORMAT_R32G32B32_SINT;
            case ShaderDataType::Int4:    return VK_FORMAT_R32G32B32A32_SINT;
            case ShaderDataType::Bool:    return VK_FORMAT_R8_UINT;
            case ShaderDataType::Mat3:    return VK_FORMAT_R32G32B32_SFLOAT;
            case ShaderDataType::Mat4:    return VK_FORMAT_R32G32B32A32_SFLOAT;
            default: QB_CORE_ASSERT(false, "Unknown ShaderDataType!"); return VK_FORMAT_UNDEFINED;
            }
        }
    }


	VulkanVertexArray::VulkanVertexArray()
	{

	}

	VulkanVertexArray::~VulkanVertexArray()
	{
	}

	void VulkanVertexArray::Bind() const
	{
	}

	void VulkanVertexArray::Unbind() const
	{
	}

    /**
     * @brief Adds a vertex buffer to the array.
     * @param vertexBuffer The vertex buffer to add.
     *
     * @details
     * This function adds a vertex buffer to the vertex array
     * and uses the the vertex buffers layout to set vertex input description
     * for the vulkan pipeline.
     */
    void VulkanVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
    {
        QB_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

        Bind();
        vertexBuffer->Bind();

        const auto& layout = vertexBuffer->GetLayout();



        uint32_t bindingIndex = 0;

        VkVertexInputBindingDescription bindingDescription = {};
        bindingDescription.binding = m_VertexBufferIndex; /* Which vertex buffer in vertex buffer array */
        bindingDescription.stride = layout.GetStride();
        bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

        for (const auto& element : layout)
        {

            VkVertexInputAttributeDescription attributeDescription = {};
            attributeDescription.binding = m_VertexBufferIndex;
            attributeDescription.location = bindingIndex;
            attributeDescription.format = Util::ShaderDataTypeToVulkanFormat(element.Type);
            attributeDescription.offset = element.Offset;

            m_AttributeDescriptions.push_back(attributeDescription);

            bindingIndex++;
        }

        m_BindingDescriptions.push_back(bindingDescription);

        VkPipelineVertexInputStateCreateInfo vertexInputInfo = {};
        vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
        vertexInputInfo.vertexBindingDescriptionCount = static_cast<uint32_t>(m_BindingDescriptions.size());
        vertexInputInfo.pVertexBindingDescriptions = m_BindingDescriptions.data();
        vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(m_AttributeDescriptions.size());
        vertexInputInfo.pVertexAttributeDescriptions = m_AttributeDescriptions.data();


        m_VertexBuffers.push_back(vertexBuffer);
        m_VertexBufferIndex++; /* It will guarantee that newly added Vertex buffer will have idx +1 */
    }



	void VulkanVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
	}



}