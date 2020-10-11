#include "SwapChain.hpp"



namespace Hyades
{
    SwapChain::SwapChain(VkSurfaceKHR& surface, GLFWwindow *window) : m_surface(surface), m_window(window)
    {   }

    SwapChain::~SwapChain()
    {   
        clean();
    }

    SwapChainSupportDetails SwapChain::query_swap_chain_support(VkPhysicalDevice device)
    {
        SwapChainSupportDetails details;

        vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, m_surface, &details.capabilities);

        uint32_t formatCount;
        vkGetPhysicalDeviceSurfaceFormatsKHR(device, m_surface, &formatCount, nullptr);

        if (formatCount != 0)
        {
            details.formats.resize(formatCount);
            vkGetPhysicalDeviceSurfaceFormatsKHR(device, m_surface, &formatCount, details.formats.data());
        }

        uint32_t presentModeCount;
        vkGetPhysicalDeviceSurfacePresentModesKHR(device, m_surface, &presentModeCount, nullptr);

        if (presentModeCount != 0)
        {
            details.presentModes.resize(presentModeCount);
            vkGetPhysicalDeviceSurfacePresentModesKHR(device, m_surface, &presentModeCount, details.presentModes.data());
        }

        // swapChainSupport = details;
        return details;
    }

    VkSurfaceFormatKHR SwapChain::choose_surface_format(const std::vector<VkSurfaceFormatKHR> &available_formats)
    {
        for (const auto &availableFormat : available_formats)
        {
            if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
            {
                return availableFormat;
            }
        }

        return available_formats[0];
    }

    VkPresentModeKHR SwapChain::choose_present_mode(const std::vector<VkPresentModeKHR> &available_present_modes)
    {
        for (const auto &availablePresentMode : available_present_modes)
        {
            if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR)
            {
                return availablePresentMode;
            }
        }

        return VK_PRESENT_MODE_FIFO_KHR;
    }


    VkExtent2D SwapChain::choose_extent(const VkSurfaceCapabilitiesKHR &capabilities)
    {

        // return capabilities.currentExtent;
        if (capabilities.currentExtent.width != UINT32_MAX)
        {
            return capabilities.currentExtent;
        }
        else
        {
            int width, height;
            glfwGetFramebufferSize(m_window, &width, &height);

            VkExtent2D actualExtent = {
                static_cast<uint32_t>(width),
                static_cast<uint32_t>(height)};

            actualExtent.width = std::max(capabilities.minImageExtent.width, std::min(capabilities.maxImageExtent.width, actualExtent.width));
            actualExtent.height = std::max(capabilities.minImageExtent.height, std::min(capabilities.maxImageExtent.height, actualExtent.height));

            return actualExtent;
        }
    }

    void SwapChain::create(VkPhysicalDevice physical_device, QueueFamilyIndices indices, VkDevice device)
    {

        m_device = device;
        swap_chain_support = query_swap_chain_support(physical_device);

        VkSurfaceFormatKHR surfaceFormat = choose_surface_format(swap_chain_support.formats);
        VkPresentModeKHR presentMode = choose_present_mode(swap_chain_support.presentModes);
        VkExtent2D extent = choose_extent(swap_chain_support.capabilities);

        uint32_t imageCount = swap_chain_support.capabilities.minImageCount + 1;
        if (swap_chain_support.capabilities.maxImageCount > 0 && imageCount > swap_chain_support.capabilities.maxImageCount)
        {
            imageCount = swap_chain_support.capabilities.maxImageCount;
        }

        VkSwapchainCreateInfoKHR swap_chain_create_info{};
        swap_chain_create_info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
        swap_chain_create_info.surface = m_surface;

        swap_chain_create_info.minImageCount = imageCount;
        swap_chain_create_info.imageFormat = surfaceFormat.format;
        swap_chain_create_info.imageColorSpace = surfaceFormat.colorSpace;
        swap_chain_create_info.imageExtent = extent;
        swap_chain_create_info.imageArrayLayers = 1;
        swap_chain_create_info.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

        uint32_t queueFamilyIndices[] = {indices.graphics_family.value(), indices.present_family.value()};

        if (indices.graphics_family != indices.present_family)
        {
            swap_chain_create_info.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
            swap_chain_create_info.queueFamilyIndexCount = 2;
            swap_chain_create_info.pQueueFamilyIndices = queueFamilyIndices;
        }
        else
        {
            swap_chain_create_info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        }

        swap_chain_create_info.preTransform = swap_chain_support.capabilities.currentTransform;
        swap_chain_create_info.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
        swap_chain_create_info.presentMode = presentMode;
        swap_chain_create_info.clipped = VK_TRUE;

        if (vkCreateSwapchainKHR(device, &swap_chain_create_info, nullptr, &swapChain) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to create swap chain!");
        }

        vkGetSwapchainImagesKHR(device, swapChain, &imageCount, nullptr);
        m_images.resize(imageCount);
        vkGetSwapchainImagesKHR(device, swapChain, &imageCount, m_images.data());

        swapChainImageFormat = surfaceFormat.format;
        swapChainExtent = extent;
        
        create_image_views();
    }

    void SwapChain::create_image_views() 
    {
        m_imageviews.resize(m_images.size());

        for (size_t i = 0; i < m_images.size(); i++) 
        {
            VkImageViewCreateInfo imageview_create_info{};
            imageview_create_info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
            imageview_create_info.image = m_images[i];
            
            imageview_create_info.viewType = VK_IMAGE_VIEW_TYPE_2D;
            imageview_create_info.format = swapChainImageFormat;

            imageview_create_info.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
            imageview_create_info.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
            imageview_create_info.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
            imageview_create_info.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
            
            imageview_create_info.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
            imageview_create_info.subresourceRange.baseMipLevel = 0;
            imageview_create_info.subresourceRange.levelCount = 1;
            imageview_create_info.subresourceRange.baseArrayLayer = 0;
            imageview_create_info.subresourceRange.layerCount = 1;

            if (vkCreateImageView(m_device, &imageview_create_info, nullptr, &m_imageviews[i]) != VK_SUCCESS) 
            {
                throw std::runtime_error("failed to create image views!");
            }
        }
    }

    void SwapChain::clean()
    {
        for (auto imageview : m_imageviews) 
        {
            if (imageview != VK_NULL_HANDLE)
            {
                vkDestroyImageView(m_device, imageview, nullptr);
            }
        }
        
        if (swapChain != VK_NULL_HANDLE)
        {
            vkDestroySwapchainKHR(m_device, swapChain, nullptr);
        }
    }

    void SwapChain::create_framebuffers(const VkRenderPass& render_pass) 
    {
        m_framebuffers.resize(m_imageviews.size());

        for (size_t i = 0; i < m_imageviews.size(); i++) 
        {
            VkImageView attachments[] = { m_imageviews[i] };

            VkFramebufferCreateInfo framebufferInfo{};
            framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
            framebufferInfo.renderPass = render_pass;
            framebufferInfo.attachmentCount = 1;
            framebufferInfo.pAttachments = attachments;
            framebufferInfo.width = swapChainExtent.width;
            framebufferInfo.height = swapChainExtent.height;
            framebufferInfo.layers = 1;

            if (vkCreateFramebuffer(m_device, &framebufferInfo, nullptr, &m_framebuffers[i]) != VK_SUCCESS) {
                throw std::runtime_error("failed to create framebuffer!");
            }
        }
    }

    void SwapChain::recreate(const VkExtent2D& extent)
    {
        
        if (swapChainExtent.width != extent.width || swapChainExtent.height != extent.height)
        {
            swapChainExtent = extent;
        }

        create_image_views();
    }

}


    