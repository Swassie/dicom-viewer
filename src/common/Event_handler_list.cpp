#include "common/Event_handler_list.h"

Event_handler_list::~Event_handler_list() {
    remove_all();
}

void Event_handler_list::add(const Handler_remover& remover) {
    m_handler_removers.push_back(remover);
}

void Event_handler_list::remove_all() {
    for(const auto& handler_remover : m_handler_removers) {
        handler_remover();
    }
    m_handler_removers.clear();
}
