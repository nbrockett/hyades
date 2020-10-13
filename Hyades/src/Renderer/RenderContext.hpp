#pragma once

// #ifndef GLFW_INCLUDE_VULKAN
// #define GLFW_INCLUDE_VULKAN
// #endif

//
#include "Renderer.hpp"
#define GLFW_INCLUDE_VULKAN
#include <vulkan/vulkan.h>

#include "GLFW/glfw3.h"
#include "SwapChain.hpp"
// #include "../Window.hpp"
#include "QueueFamily.hpp"
#include <fstream>
namespace Hyades
{

    static std::vector<char> readFile(const std::string& filename) 
    {
        std::ifstream file(filename, std::ios::ate | std::ios::binary);

        if (!file.is_open()) {
            throw std::runtime_error(std::string("failed to open file ") + filename);
        }

        size_t fileSize = (size_t) file.tellg();
        std::vector<char> buffer(fileSize);

        file.seekg(0);
        file.read(buffer.data(), fileSize);

        file.close();

        return buffer;
    }

    class Window;

    class RenderContext
    {
    private:

        vk::Instance m_instance;
        VkDebugUtilsMessengerEXT m_debug_messenger;
        VkSurfaceKHR m_surface;
        
        vk::PhysicalDevice m_physical_device;
        std::vector<vk::PhysicalDevice> m_physical_devices;

        VkQueue m_graphics_queue;
        VkQueue m_present_queue;

        SwapChain swapChain;

        // TODO: move to different class
        VkRenderPass renderPass;
        VkPipelineLayout pipelineLayout;
        VkPipeline graphicsPipeline;

        // TODO: move to different class
        VkCommandPool commandPool;
        std::vector<VkCommandBuffer> commandBuffers;

        // TODO: move to a different class
        std::vector<VkSemaphore> imageAvailableSemaphores;
        std::vector<VkSemaphore> renderFinishedSemaphores;
        std::vector<VkFence> inFlightFences;
        std::vector<VkFence> imagesInFlight;

        const bool use_validation_layers = true;

        const std::vector<const char *> validationLayers = {
            "VK_LAYER_KHRONOS_validation"
        };

        const std::vector<const char *> deviceExtensions = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME
        };

        VulkanRenderer m_renderer = VulkanRenderer();

        GLFWwindow *m_window;

    public:
        RenderContext(GLFWwindow *window);
        ~RenderContext();

        VkDevice m_device;

        void init();
        void destroy();

        void create_instance();
        void create_surface();
        void choose_physical_device();
        void create_logical_device();
        void create_swap_chain();
        void create_render_pass();
        void create_graphics_pipeline();
        void create_command_pool();
        void create_command_buffers();
        void create_sync_objects();

        void recreateSwapChain();

        void drawFrame();

        bool is_device_suitable(vk::PhysicalDevice device);
        bool check_device_extension_support(vk::PhysicalDevice device);
        QueueFamilyIndices find_queue_families(VkPhysicalDevice device);

        VkShaderModule createShaderModule(const std::vector<char>& code);

        static void on_window_resize(uint32_t width, uint32_t height);

        void render();
        bool check_validation_layer_support();
        std::vector<const char *> get_required_extensions();
        void populate_debug_info(VkDebugUtilsMessengerCreateInfoEXT &createInfo);
        void setup_debug_messenger();
    };
} // namespace Hyades
