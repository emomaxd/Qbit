#pragma once

#include "Qbit/Renderer/GraphicsContext.h"

#ifdef QB_PLATFORM_WINDOWS
#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_EXPOSE_NATIVE_WIN32
#endif

#include <vulkan/vulkan.h>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include <optional>


struct GLFWwindow;

namespace Qbit {
    struct QueueFamilyIndices;
    struct SwapChainSupportDetails;

    class VulkanContext : public GraphicsContext
    {
    public:
        VulkanContext(GLFWwindow* windowHandle);
        ~VulkanContext();

        void Init();
        void SwapBuffers();
        VkDevice& GetDevice() { return m_Device; }
        void RecreateSwapChain();
        void SetResized(bool enable) { m_FramebufferResized = true; }

    private:
        void CleanupSwapChain();

    private:
        void OnWindowResize(int width, int height);

    private: /* Setup */
        void CreateInstance();
        void SetupDebugMessenger();
        void PickPhysicalDevice();
        void CreateLogicalDevice();
        void CreateSurface();
        void CreateSwapChain();
        void CreateImageViews();
        void CreateRenderPass();
        void CreateGraphicsPipeline();
        void CreateFramebuffers();
        void CreateCommandPool();
        void RecordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
        void CreateSemaphores();
    
    private: /* Setup helpers */
        bool CheckValidationLayerSupport();
        bool CheckDeviceExtensionSupport(VkPhysicalDevice device);
        std::vector<const char*> GetRequiredExtensions() const;
        QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device) const;
        SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device) const;

        VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
        VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
        VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

        VkShaderModule CreateShaderModule(const std::vector<char>& code);

    private:
        void DrawFrame(); // Tester function for early vulkan testing
        

    private:
        GLFWwindow* m_WindowHandle;

        VkInstance m_Instance;
        VkDebugUtilsMessengerEXT m_DebugMessenger;
        
        VkPhysicalDevice m_PhysicalDevice = VK_NULL_HANDLE;
        VkDevice m_Device;
        
        VkQueue m_GraphicsQueue;
        VkQueue m_PresentQueue;
        VkSurfaceKHR m_Surface;

        VkSwapchainKHR m_SwapChain;
        std::vector<VkImage> m_SwapChainImages;
        VkFormat m_SwapChainImageFormat;
        VkExtent2D m_SwapChainExtent;
        std::vector<VkImageView> m_SwapChainImageViews;

        VkRenderPass m_RenderPass;
        VkPipelineLayout m_PipelineLayout;
        VkPipeline m_GraphicsPipeline;

        std::vector<VkFramebuffer> m_SwapChainFramebuffers;

        VkCommandPool m_CommandPool;
        std::vector<VkCommandBuffer> m_CommandBuffers;

        std::vector<VkSemaphore> m_ImageAvailableSemaphores;
        std::vector<VkSemaphore> m_RenderFinishedSemaphores;
        std::vector<VkFence> m_InFlightFences;

    private:
#ifdef QB_DEBUG
        const bool ENABLE_VALIDATION_LAYERS = true;
#else
        const bool ENABLE_VALIDATION_LAYERS = false;
#endif

        const size_t MAX_FRAMES_IN_FLIGHT = 2;

        uint32_t m_CurrentFrame = 0;

        bool m_FramebufferResized = false;

        const float ASPECT_RATIO = 1.778f;

        const std::vector<const char*> m_ValidationLayers =
        {
            "VK_LAYER_KHRONOS_validation"
        };

        const std::vector<const char*> m_DeviceExtensions =
        {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME
        };

        const std::vector<VkDynamicState> m_DynamicStates =
        {
            VK_DYNAMIC_STATE_VIEWPORT,
            VK_DYNAMIC_STATE_SCISSOR
        };

    };

}
