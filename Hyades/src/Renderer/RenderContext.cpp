#include "RenderContext.hpp"
#include <vulkan/vulkan.h>
#include "GLFW/glfw3.h"

namespace Hyades
{

    VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) 
    {
        auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
        if (func != nullptr) {
            return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
        } else {
            return VK_ERROR_EXTENSION_NOT_PRESENT;
        }
    }

    void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) 
    {
        auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
        if (func != nullptr) {
            func(instance, debugMessenger, pAllocator);
        }
    }


    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData) 
    {

        std::string info_string = std::string("validation layer: ") + pCallbackData->pMessage;

        switch (messageSeverity)
        {
            case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
                Hyades::Logger::s_logger->debug(info_string);
                break;
            case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
                Hyades::Logger::s_logger->warn(info_string);
                break;
            case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
                Hyades::Logger::s_logger->warn(info_string);
                break;
            case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
                Hyades::Logger::s_logger->error(info_string);
                break;
            default:
                Hyades::Logger::s_logger->error(info_string);
        }

        return VK_FALSE;
    }



    RenderContext::RenderContext(/* args */)
    {
        init();
    }

    RenderContext::~RenderContext()
    {   }

    void RenderContext::destroy()
    {
        Hyades::Logger::s_logger->debug("Destroying Render Context");

        // destroy vulkan debug messenger
        if (enable_validation_layers) {
            DestroyDebugUtilsMessengerEXT(m_vk_instance, m_debug_messenger, nullptr);
        }

        // destroy vulkan instance
        vkDestroyInstance(m_vk_instance, nullptr);
    }

    void RenderContext::on_window_resize(u_int32_t width, uint32_t height)
    {
        

    }

    void RenderContext::render()
    {
        // Logger::s_logger->info("rendering context frame...");
    }

    void RenderContext::init()
    {
        create_instance();
        setup_debug_messenger();
    }

    bool RenderContext::check_validation_layer_support() {
        uint32_t layer_count;
        vkEnumerateInstanceLayerProperties(&layer_count, nullptr);

        std::vector<VkLayerProperties> available_layers(layer_count);
        vkEnumerateInstanceLayerProperties(&layer_count, available_layers.data());

        for (const auto layerName : validationLayers) {
            bool layer_found = false;

            for (const auto& layer_properties : available_layers) {
                if (strcmp(layerName, layer_properties.layerName) == 0) {
                    layer_found = true;
                    break;
                }
            }

            if (!layer_found) {
                return false;
            }
        }

        return true;
    }

    void RenderContext::create_instance()
    {
        if (enable_validation_layers && !check_validation_layer_support()) {
            Hyades::Logger::s_logger->error("Couldn't find any Vulkan validation layers");
            throw std::runtime_error("validation layers requested, but not available!");
        }

        // Application Info
        VkApplicationInfo vk_app_info{};
        vk_app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        vk_app_info.pApplicationName = "Hyades App";
        vk_app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        vk_app_info.pEngineName = "Hyades";
        vk_app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        vk_app_info.apiVersion = VK_API_VERSION_1_0;

        // Instance Info
        VkInstanceCreateInfo vk_instance_info{};
        vk_instance_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        vk_instance_info.pApplicationInfo = &vk_app_info;


        auto extensions = RenderContext::get_required_extensions();
        vk_instance_info.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
        vk_instance_info.ppEnabledExtensionNames = extensions.data();

        VkDebugUtilsMessengerCreateInfoEXT vk_debug_info;
        if (enable_validation_layers) {
            vk_instance_info.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
            vk_instance_info.ppEnabledLayerNames = validationLayers.data();

            populate_debug_info(vk_debug_info);
            vk_instance_info.pNext = (VkDebugUtilsMessengerCreateInfoEXT*) &vk_debug_info;
        } else {
            vk_instance_info.enabledLayerCount = 0;
            vk_instance_info.pNext = nullptr;
        }

        if (vkCreateInstance(&vk_instance_info, nullptr, &m_vk_instance) != VK_SUCCESS) {
            throw std::runtime_error("failed to create instance!");
        }
    }

    std::vector<const char*> RenderContext::get_required_extensions() 
    {

        // extension to interface with GLFW
        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
        // glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
        // const char** glfwExtensions = new char*[10] {"Nope"};

        std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

        if (enable_validation_layers) {
            extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        }

        return extensions;
    }

    void RenderContext::populate_debug_info(VkDebugUtilsMessengerCreateInfoEXT& create_info) {
        create_info = {};
        create_info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        create_info.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        create_info.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        create_info.pfnUserCallback = Hyades::debugCallback;
    }

    void RenderContext::setup_debug_messenger() {
        if (!enable_validation_layers) return;

        VkDebugUtilsMessengerCreateInfoEXT debug_info;
        populate_debug_info(debug_info);

        if (CreateDebugUtilsMessengerEXT(m_vk_instance, &debug_info, nullptr, &m_debug_messenger) != VK_SUCCESS) {
            throw std::runtime_error("failed to set up debug messenger!");
        }
    }



} // namespace Hyades

