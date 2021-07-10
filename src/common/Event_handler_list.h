#pragma once
#include <functional>
#include <vector>

/* Helps manage the lifetime of event handlers,
 * regardless of the Event template specialization. */
class Event_handler_list
{
public:
    using Handler_remover = std::function<void()>;

    ~Event_handler_list();

    void add(const Handler_remover&);
    void remove_all();

protected:
    std::vector<Handler_remover> m_handler_removers;
};
