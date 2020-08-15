#pragma once

#include "Renderer.hpp"

namespace Hyades
{
    class RenderContext
    {
    private:
        


        VulkanRenderer m_renderer = VulkanRenderer();
    public:
        RenderContext(/* args */);
        ~RenderContext();

        static void on_window_resize(uint32_t width, uint32_t height);

        void render();

    };
    
    
} // namespace Hyades

