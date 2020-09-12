#pragma once

#include <vulkan/vulkan.h>
#include "../HyadesPCH.hpp"
#include "QueueFamily.hpp"

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

        VkSwapchainKHR swapChain;
        SwapChainSupportDetails swapChainSupport;


        std::vector<VkImage> swapChainImages;
        VkFormat swapChainImageFormat;
        VkExtent2D swapChainExtent;
        std::vector<VkImageView> swapChainImageViews;
        std::vector<VkFramebuffer> swapChainFramebuffers;

    protected:
        VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats);
        VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes);
        VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities);
    public:
        SwapChain(VkSurfaceKHR& surface);
        ~SwapChain();

        void create(VkPhysicalDevice physical_device, QueueFamilyIndices indices, VkDevice device);

        void query_swap_chain_support(VkPhysicalDevice device);

        void clean();


    };
        
} // namespace Hyades



