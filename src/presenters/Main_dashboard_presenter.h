#pragma once
#include "presenters/Main_presenter.h"

class IMain_view;

class Main_dashboard_presenter : public Main_presenter
{
public:
    Main_dashboard_presenter(IMain_view&);

    void setup_event_handlers() override;
    void setup_view() override;

protected:
    IMain_view& m_view;
};
