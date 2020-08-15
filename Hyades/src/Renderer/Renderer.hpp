#pragma once

#include "../HyadesPCH.hpp"

namespace Hyades
{
    
    class Renderer
    {
    private:
        /* data */
    public:
        Renderer(/* args */);
        ~Renderer();
    };


    class VulkanRenderer : public Renderer
    {
    private:
        /* data */
    public:
        VulkanRenderer(/* args */);
        ~VulkanRenderer();
    };
    

    

} // namespace Hyades

