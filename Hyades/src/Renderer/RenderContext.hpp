#pragma once

// #ifndef GLFW_INCLUDE_VULKAN 
// #define GLFW_INCLUDE_VULKAN
// #endif

// 
#include "Renderer.hpp"
#define GLFW_INCLUDE_VULKAN
#include <vulkan/vulkan.h>
#include "GLFW/glfw3.h"
// #include "../Window.hpp"



namespace Hyades
{

    struct SwapChainSupportDetails 
    {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };

    struct QueueFamilyIndices 
    {
        std::optional<uint32_t> graphics_family;
        std::optional<uint32_t> present_family;

        bool is_complete() {
            return graphics_family.has_value() && present_family.has_value();
        }
    };

    class Window;

    class RenderContext
    {
    private:
    
        VkInstance m_vk_instance;
        VkDebugUtilsMessengerEXT m_debug_messenger;
        VkSurfaceKHR m_surface;
        VkPhysicalDevice m_physical_device{ VK_NULL_HANDLE };
        VkDevice m_device;

        VkQueue m_graphics_queue;
        VkQueue m_present_queue;

        // swap chain vars
        VkSwapchainKHR swapChain;
        std::vector<VkImage> swapChainImages;
        VkFormat swapChainImageFormat;
        VkExtent2D swapChainExtent;
        std::vector<VkImageView> swapChainImageViews;
        std::vector<VkFramebuffer> swapChainFramebuffers;


        const bool use_validation_layers = true;

        const std::vector<const char*> validationLayers = {
            "VK_LAYER_KHRONOS_validation"
        };

        const std::vector<const char*> deviceExtensions = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME
        };
        

        VulkanRenderer m_renderer = VulkanRenderer();

        GLFWwindow* m_window;

    public:

        RenderContext(GLFWwindow* window);
        ~RenderContext();

        void init();
        void destroy();

        void create_instance();
        void create_surface();
        void choose_physical_device();
        void create_logical_device();
        void create_swap_chain();

        bool is_device_suitable(VkPhysicalDevice device);
        bool check_device_extension_support(VkPhysicalDevice device);
        QueueFamilyIndices find_queue_families(VkPhysicalDevice device);
        SwapChainSupportDetails query_swap_chain_support(VkPhysicalDevice device); 

        VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
        VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes); 
        VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);



        static void on_window_resize(uint32_t width, uint32_t height);

        void render();
        bool check_validation_layer_support();
        std::vector<const char*> get_required_extensions();
        void populate_debug_info(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
        void setup_debug_messenger();
    };
    
    
} // namespace Hyades

