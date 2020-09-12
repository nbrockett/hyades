#pragma once

#include <vulkan/vulkan.h>
#include "../HyadesPCH.hpp"

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

        VkSwapchainKHR swapChain;
        std::vector<VkImage> swapChainImages;
    public:
        SwapChain(VkSurfaceKHR& surface);
        ~SwapChain();

        SwapChainSupportDetails query_swap_chain_support(VkPhysicalDevice device);
    

    };
        
} // namespace Hyades



