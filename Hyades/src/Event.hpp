#pragma once

#include "HyadesPCH.hpp"

namespace Hyades
{



    enum class EventType 
    {
        WindowClose, WindowResize
    };


    class Event
    {
    private:
        // EventType m_type = 0

    public:
        virtual ~Event() = default;
        // virtual Event() = 0;
    
        virtual EventType type() const = 0;
    
    
    };


    class WindowCloseEvent : public Event
    {
    public:
        WindowCloseEvent()
        {   }

        EventType type() const { return m_type; }

        static constexpr EventType m_type = EventType::WindowClose;
    private:
        

    };

    class WindowResizeEvent : public Event
    {
    public:
        WindowResizeEvent(size_t width, size_t height) : m_width(width), m_height(height)
        {   }

        size_t const& width() const { return m_width; };
        size_t const& height() const { return m_height; };

        EventType type() const { return m_type; }

        static constexpr EventType m_type = EventType::WindowResize;
        
    private:
        size_t m_width;
        size_t m_height;
    };


    class EventHandler
    {
    public:
        EventHandler() = default;

        // template<typename T>
        void add_handler(std::function<void(const WindowCloseEvent&)> callback_func)
        {
            // [] operator creates key if doesn't exists
            m_handler_map[WindowCloseEvent::m_type].push_back(callback_func);

        }

        void trigger(const WindowCloseEvent& event)
        {
            const auto event_type = event.type();

            if (m_handler_map.contains(event_type)) {
                for (const auto& handle : m_handler_map.at(event_type))
                {   
                    std::invoke(handle, event);
                }
            }

        }


    private:
        std::map<EventType, std::vector< std::function<void(const WindowCloseEvent&)> > > m_handler_map;

    };


} // namespace Hyades




