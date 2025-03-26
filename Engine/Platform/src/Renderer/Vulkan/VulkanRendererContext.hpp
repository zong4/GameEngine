#pragma once

#include "../RendererContext.hpp"
#include <vulkan/vulkan.h>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace Engine {
class VulkanRendererContext final : public RendererContext
{
public:
    explicit VulkanRendererContext(void* windowHandle, bool vsync);
    virtual ~VulkanRendererContext();
    VulkanRendererContext(const VulkanRendererContext&) = delete;
    VulkanRendererContext& operator=(const VulkanRendererContext&) = delete;

    virtual void SwapBuffers() override;

public:
    VkDevice GetDevice() { return m_Device; }

private:
    void CreateInstance();
    std::vector<const char*> GetRequiredExtensions();

    bool CheckValidationLayerSupport();
    void SetupDebugMessenger();
    void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
    VkResult CreateDebugUtilsMessengerEXT(VkInstance instance,
                                          const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
                                          const VkAllocationCallbacks* pAllocator,
                                          VkDebugUtilsMessengerEXT* pDebugMessenger);
    void DestroyDebugUtilsMessengerEXT(VkInstance instance,
                                       VkDebugUtilsMessengerEXT debugMessenger,
                                       const VkAllocationCallbacks* pAllocator);
    static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                                                        VkDebugUtilsMessageTypeFlagsEXT messageType,
                                                        const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
                                                        void* pUserData);

    void CreateSurface();

    void PickPhysicalDevice();
    bool IsDeviceSuitable(VkPhysicalDevice device);
    int RateDeviceSuitability(VkPhysicalDevice device);
    bool CheckDeviceExtensionSupport(VkPhysicalDevice device);

    struct QueueFamilyIndices
    {
        std::optional<uint32_t> GraphicsFamily;
        std::optional<uint32_t> PresentFamily;

        bool IsComplete() { return GraphicsFamily.has_value() && PresentFamily.has_value(); }
    };
    QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);
    void CreateLogicalDevice();

    struct SwapChainSupportDetails
    {
        VkSurfaceCapabilitiesKHR Capabilities;
        std::vector<VkSurfaceFormatKHR> Formats;
        std::vector<VkPresentModeKHR> PresentModes;
    };
    SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device);
    VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
    VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
    VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
    void CreateSwapChain();

    void CreateImageViews();

private:
    VkInstance m_Instance;

#ifdef DEBUG
    bool m_EnableValidationLayers = true;
#elif RELEASE
    bool m_EnableValidationLayers = false;
#endif
    const std::vector<const char*> m_ValidationLayers = {
        "VK_LAYER_KHRONOS_validation",
    };
    VkDebugUtilsMessengerEXT m_DebugMessenger;

    VkSurfaceKHR m_Surface;

    const std::vector<const char*> m_DeviceExtensions = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};
    VkPhysicalDevice m_PhysicalDevice = VK_NULL_HANDLE;
    VkDevice m_Device;

    VkQueue m_GraphicsQueue;
    VkQueue m_PresentQueue;

    VkSwapchainKHR m_SwapChain;
    std::vector<VkImage> m_SwapChainImages;
    VkFormat m_SwapChainImageFormat;
    VkExtent2D m_SwapChainExtent;

    std::vector<VkImageView> m_SwapChainImageViews;
};
} // namespace Engine