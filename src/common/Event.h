#pragma once
#include "logging/Log.h"

#include <functional>
#include <utility>

template<class ... Parameters>
class Event
{
public:
    using Id = int;
    using Handler = std::function<void(Parameters...)>;

    Event()
        : m_enabled(true),
          m_next_handler_id(0) {}

    void set_enabled(bool enabled) {
        m_enabled = enabled;
    }

    Id add_handler(const Handler& handler) {
        const Id id = m_next_handler_id++;
        m_handlers.emplace_back(id, handler);
        return id;
    }

    void remove_handler(const Id id) {
        for(auto it = m_handlers.begin(); it != m_handlers.end(); ++it) {
            if(it->first == id) {
                m_handlers.erase(it);
                return;
            }
        }
        Log::debug("Could not find handler for removal.");
    }

    std::function<void()> get_handler_remover(const Id id) {
        return [this, id] {remove_handler(id);};
    }

    void trigger(Parameters... parameters) {
        if(!m_enabled) {
            return;
        }
        /* Iterate over a local copy of m_handlers to avoid the problem with
         * iterator invalidation, since each handler might add/remove handlers. */
        const auto handlers = m_handlers;
        for(const auto& handler : handlers) {
            handler.second(parameters...);
        }
    }

protected:
    bool m_enabled;
    Id m_next_handler_id;
    std::vector<std::pair<Id, Handler>> m_handlers;
};
