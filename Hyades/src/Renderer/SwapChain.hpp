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
    private:
        const VkSurfaceKHR& m_surface;
        VkDevice m_device;
        GLFWwindow *m_window;

        SwapChainSupportDetails swapChainSupport;

    protected:
        VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats);
        VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes);
        VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities);

        void createImageViews();
    public:
        SwapChain(VkSurfaceKHR& surface, GLFWwindow *window);
        ~SwapChain();

        VkSwapchainKHR swapChain;

        VkFormat swapChainImageFormat;
        VkExtent2D swapChainExtent;

        // TODO: move these to seperate location/class
        std::vector<VkImageView> swapChainImageViews;
        std::vector<VkFramebuffer> swapChainFramebuffers;

        std::vector<VkImage> swapChainImages;


        void create(VkPhysicalDevice physical_device, QueueFamilyIndices indices, VkDevice device);

        void query_swap_chain_support(VkPhysicalDevice device);

        void clean();

    };
        
} // namespace Hyades



