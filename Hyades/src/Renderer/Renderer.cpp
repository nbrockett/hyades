#include "Renderer.hpp"
#include "../Logger.hpp"


namespace Hyades
{
    
    Renderer::Renderer(/* args */)
    {
    }

    Renderer::~Renderer()
    {
    }
    
    VulkanRenderer::VulkanRenderer(/* args */)
    {
    }
    
    VulkanRenderer::~VulkanRenderer()
    {
    }

    void VulkanRenderer::render()
    {
        Logger::s_logger->info("rendering frame...");
    }


} // namespace Hyades

