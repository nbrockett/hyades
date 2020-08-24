#pragma once

// #ifndef GLFW_INCLUDE_VULKAN 
// #define GLFW_INCLUDE_VULKAN
// #endif

// 
#include "Renderer.hpp"
#include <vulkan/vulkan.h>
#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"
// #include "../Window.hpp"



namespace Hyades
{

    class Window;

    class RenderContext
    {
    private:
    
        VkInstance m_vk_instance;
        VkDebugUtilsMessengerEXT m_debug_messenger;
        VkSurfaceKHR m_surface;

        #ifdef NDEBUG
        const bool use_validation_layers = false;
        #else
        const bool use_validation_layers = true;
        #endif

        const std::vector<const char*> validationLayers = {
            "VK_LAYER_KHRONOS_validation"
        };

        

        VulkanRenderer m_renderer = VulkanRenderer();

        const GLFWwindow* m_window;

    public:

        RenderContext(const GLFWwindow* window);
        ~RenderContext();

        void init();
        void destroy();

        void create_instance();
        void create_surface();

        static void on_window_resize(uint32_t width, uint32_t height);

        void render();
        bool check_validation_layer_support();
        std::vector<const char*> get_required_extensions();
        void populate_debug_info(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
        void setup_debug_messenger();
    };
    
    
} // namespace Hyades

