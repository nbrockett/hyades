#include "RenderContext.hpp"

namespace Hyades
{
    RenderContext::RenderContext(/* args */)
    {
    }

    RenderContext::~RenderContext()
    {
    }

    void RenderContext::on_window_resize(u_int32_t width, uint32_t height)
    {
        

    }

    void RenderContext::render()
    {
        Logger::s_logger->info("rendering context frame...");
    }

} // namespace Hyades

