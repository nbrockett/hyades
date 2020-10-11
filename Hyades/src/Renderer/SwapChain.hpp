// SwapChain
//
// The swap chain own the image buffer and synchronisies their presentation
//



#pragma once

#include <vulkan/vulkan.h>
#include "../HyadesPCH.hpp"
#include "QueueFamily.hpp"
#include "GLFW/glfw3.h"

namespace Hyades
{

    struct SwapChainSupportDetails
    {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };

    class SwapChain
    {
    public:

        SwapChain(VkSurfaceKHR& surface, GLFWwindow *window);
        ~SwapChain();

        void create(VkPhysicalDevice physical_device, QueueFamilyIndices indices, VkDevice device);
        void recreate(const VkExtent2D& extent);

        void create_image_views();
        void create_framebuffers(const VkRenderPass& render_pass);
        SwapChainSupportDetails query_swap_chain_support(VkPhysicalDevice device);
        void clean();
        
        VkSurfaceFormatKHR choose_surface_format(const std::vector<VkSurfaceFormatKHR> &available_formats);
        VkPresentModeKHR choose_present_mode(const std::vector<VkPresentModeKHR> &available_present_modes);
        VkExtent2D choose_extent(const VkSurfaceCapabilitiesKHR &capabilities);

        VkSwapchainKHR swapChain = VK_NULL_HANDLE;

        VkFormat swapChainImageFormat;
        VkExtent2D swapChainExtent;

        // TODO: move these to seperate location/class
        std::vector<VkImageView> m_imageviews;
        std::vector<VkFramebuffer> m_framebuffers;

        std::vector<VkImage> m_images;

    private:
        const VkSurfaceKHR& m_surface;
        VkDevice m_device;
        GLFWwindow *m_window;

        SwapChainSupportDetails swap_chain_support;
    };
        
} // namespace Hyades



