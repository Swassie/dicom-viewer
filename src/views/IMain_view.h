#pragma once
#include "common/Event.h"

class QString;

class IMain_view
{
public:
    virtual ~IMain_view() = default;

    Event<> open_files_event;
    Event<> quit_event;
    Event<> about_event;

    virtual void set_dashboard_view() = 0;
    virtual void set_editor_view() = 0;

    virtual void set_window_modified(bool) = 0;
    virtual void set_window_title(const QString&) = 0;

    virtual bool is_ok_to_discard_changes() = 0;
};
