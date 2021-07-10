#pragma once
#include "common/Event_handler_list.h"

class Main_presenter
{
public:
    virtual ~Main_presenter() = default;

    virtual void setup_event_handlers() = 0;
    virtual void remove_event_handlers();
    virtual void setup_view() = 0;

protected:
    Event_handler_list m_handler_list;
};
