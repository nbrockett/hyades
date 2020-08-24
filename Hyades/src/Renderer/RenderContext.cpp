#include "RenderContext.hpp"
// #include <vulkan/vulkan.h>
#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"
#include "../Window.hpp"

#include "../HyadesPCH.hpp"

namespace Hyades
{

    


    VkResult create_debug_messenger(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) 
    {
        auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
        if (func != nullptr) {
            return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
        } else {
            return VK_ERROR_EXTENSION_NOT_PRESENT;
        }
    }

    void destroy_debug_messenger(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) 
    {
        auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
        if (func != nullptr) {
            func(instance, debugMessenger, pAllocator);
        }
    }


    static VKAPI_ATTR VkBool32 VKAPI_CALL debug_callback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData) 
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


    RenderContext::RenderContext(GLFWwindow* window) : m_window(window)
    {   }

    RenderContext::~RenderContext()
    {   }

    void RenderContext::destroy()
    {
        Hyades::Logger::s_logger->debug("Destroying Render Context");

        // destroy vulkan debug messenger
        if (use_validation_layers) {
            destroy_debug_messenger(m_vk_instance, m_debug_messenger, nullptr);
        }

        vkDestroySurfaceKHR(m_vk_instance, m_surface, nullptr);
        vkDestroyInstance(m_vk_instance, nullptr);
    }

    void RenderContext::on_window_resize(u_int32_t width, uint32_t height)
    {
        

    }

    void RenderContext::render()
    {
        Logger::s_logger->info("rendering context frame...");
    }

    void RenderContext::init()
    {
        create_instance();
        setup_debug_messenger();
        create_surface();
        choose_physical_device();
        create_logical_device();
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
        if (use_validation_layers && !check_validation_layer_support()) {
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

        // setup debug info for instance creation and destruction
        VkDebugUtilsMessengerCreateInfoEXT vk_debug_info;


        if (use_validation_layers) {
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

    void RenderContext::create_surface() 
    {
        VkResult result = glfwCreateWindowSurface(m_vk_instance, m_window, nullptr, &m_surface);
        if (result != VK_SUCCESS) 
        {
            Hyades::Logger::s_logger->critical(result);
            throw std::runtime_error("failed to create window surface!");
        }
    }

    SwapChainSupportDetails RenderContext::query_swap_chain_support(VkPhysicalDevice device) 
    {
        SwapChainSupportDetails details;

        vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, m_surface, &details.capabilities);

        uint32_t formatCount;
        vkGetPhysicalDeviceSurfaceFormatsKHR(device, m_surface, &formatCount, nullptr);

        if (formatCount != 0) {
            details.formats.resize(formatCount);
            vkGetPhysicalDeviceSurfaceFormatsKHR(device, m_surface, &formatCount, details.formats.data());
        }

        uint32_t presentModeCount;
        vkGetPhysicalDeviceSurfacePresentModesKHR(device, m_surface, &presentModeCount, nullptr);

        if (presentModeCount != 0) {
            details.presentModes.resize(presentModeCount);
            vkGetPhysicalDeviceSurfacePresentModesKHR(device, m_surface, &presentModeCount, details.presentModes.data());
        }

        return details;
    }

    bool RenderContext::is_device_suitable(VkPhysicalDevice device) 
    {
        QueueFamilyIndices indices = find_queue_families(device);

        bool extensionsSupported = check_device_extension_support(device);

        bool swapChainAdequate = false;
        if (extensionsSupported) {
            SwapChainSupportDetails swapChainSupport = query_swap_chain_support(device);
            swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
        }

        return indices.is_complete() && extensionsSupported && swapChainAdequate;
    }

    bool RenderContext::check_device_extension_support(VkPhysicalDevice device)
    {
        uint32_t extensionCount;
        vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

        std::vector<VkExtensionProperties> availableExtensions(extensionCount);
        vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

        std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

        for (const auto& extension : availableExtensions) {
            requiredExtensions.erase(extension.extensionName);
        }

        return requiredExtensions.empty();
    }

    QueueFamilyIndices RenderContext::find_queue_families(VkPhysicalDevice device) 
    {
        QueueFamilyIndices indices;

        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

        int i = 0;
        for (const auto& queueFamily : queueFamilies) {
            if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
                indices.graphics_family = i;
            }

            VkBool32 presentSupport = false;
            vkGetPhysicalDeviceSurfaceSupportKHR(device, i, m_surface, &presentSupport);

            if (presentSupport) {
                indices.present_family = i;
            }

            if (indices.is_complete()) {
                break;
            }

            i++;
        }

        return indices;
    }

    void RenderContext::choose_physical_device()
    {
        uint32_t n_devices = 0;
        vkEnumeratePhysicalDevices(m_vk_instance, &n_devices, nullptr);
        
        if (n_devices == 0)
        {
            throw std::runtime_error("Failed to find any GPUs with Vulkan support");
        }

        std::vector<VkPhysicalDevice> devices(n_devices);
        vkEnumeratePhysicalDevices(m_vk_instance, &n_devices, devices.data());

        // choose first, suitable device
        for (const auto& device : devices)
        {
            if (is_device_suitable(device))
            {
                m_physical_device = device;
                break;
            }
        }

        // else no device is suitable
        if (m_physical_device == VK_NULL_HANDLE) {
            throw std::runtime_error("Failed to find suitable GPU");
        }

    }

    //************** LOGICAL DEVICE **************//
    void RenderContext::create_logical_device()
    {
        QueueFamilyIndices indices = find_queue_families(m_physical_device);
        
        std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
        std::set<uint32_t> uniqueQueueFamilies = {indices.graphics_family.value(), indices.present_family.value()};

        float queuePriority = 1.0f;
        for (uint32_t queueFamily : uniqueQueueFamilies) {
            VkDeviceQueueCreateInfo queueCreateInfo{};
            queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            queueCreateInfo.queueFamilyIndex = queueFamily;
            queueCreateInfo.queueCount = 1;
            queueCreateInfo.pQueuePriorities = &queuePriority;
            queueCreateInfos.push_back(queueCreateInfo);
        }

        VkPhysicalDeviceFeatures deviceFeatures{};

        VkDeviceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

        createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
        createInfo.pQueueCreateInfos = queueCreateInfos.data();

        createInfo.pEnabledFeatures = &deviceFeatures;

        createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
        createInfo.ppEnabledExtensionNames = deviceExtensions.data();

        if (use_validation_layers) {
            createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
            createInfo.ppEnabledLayerNames = validationLayers.data();
        } else {
            createInfo.enabledLayerCount = 0;
        }

        if (vkCreateDevice(m_physical_device, &createInfo, nullptr, &m_device) != VK_SUCCESS) {
            throw std::runtime_error("failed to create logical device!");
        }

        vkGetDeviceQueue(m_device, indices.graphics_family.value(), 0, &m_graphics_queue);
        vkGetDeviceQueue(m_device, indices.present_family.value(), 0, &m_present_queue);

    }


    //************** EXTENSIONS **************//
    std::vector<const char*> RenderContext::get_required_extensions() 
    {

        // extension to interface with GLFW
        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
        // glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
        // const char** glfwExtensions = new char*[10] {"Nope"};

        std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

        if (use_validation_layers) {
            extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        }

        return extensions;
    }

    void RenderContext::populate_debug_info(VkDebugUtilsMessengerCreateInfoEXT& create_info) {
        create_info = {};
        create_info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        create_info.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        create_info.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        create_info.pfnUserCallback = Hyades::debug_callback;
    }

    void RenderContext::setup_debug_messenger() {
        if (!use_validation_layers) return;

        VkDebugUtilsMessengerCreateInfoEXT debug_info;
        populate_debug_info(debug_info);

        // bind vulkan debug callback
        if (create_debug_messenger(m_vk_instance, &debug_info, nullptr, &m_debug_messenger) != VK_SUCCESS) {
            throw std::runtime_error("failed to set up debug messenger!");
        }
    }


} // namespace Hyades

