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

        virtual void render() = 0;
    };


    class VulkanRenderer : public Renderer
    {
    private:
        /* data */
    public:
        VulkanRenderer(/* args */);
        ~VulkanRenderer();

        void render();

    };
    

    

} // namespace Hyades

