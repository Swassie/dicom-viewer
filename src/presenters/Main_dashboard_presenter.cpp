#include "presenters/Main_dashboard_presenter.h"

#include "views/IMain_view.h"

#include <QCoreApplication>

Main_dashboard_presenter::Main_dashboard_presenter(IMain_view& view)
    : m_view(view) {}

void Main_dashboard_presenter::setup_event_handlers() {
    auto id = m_view.quit_event.add_handler([] {QCoreApplication::quit();});
    m_handler_list.add(m_view.quit_event.get_handler_remover(id));
}

void Main_dashboard_presenter::setup_view() {
    m_view.set_dashboard_view();
    m_view.set_window_modified(false);
    m_view.set_window_title(QCoreApplication::applicationName());
}
