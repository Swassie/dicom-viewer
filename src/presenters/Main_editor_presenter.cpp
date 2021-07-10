#include "presenters/Main_editor_presenter.h"

#include "models/Dicom_files.h"
#include "views/IMain_view.h"

#include <QCoreApplication>

Main_editor_presenter::Main_editor_presenter(IMain_view& view, Dicom_files& files)
    : m_view(view),
      m_files(files) {}

void Main_editor_presenter::setup_event_handlers() {
    auto id = m_view.quit_event.add_handler([this] {quit();});
    m_handler_list.add(m_view.quit_event.get_handler_remover(id));
}

void Main_editor_presenter::setup_view() {
    m_view.set_editor_view();
    // Select a file. Which triggers update of modified status and title.
}

void Main_editor_presenter::quit() {
    if(m_files.has_unsaved_changes() && !m_view.is_ok_to_discard_changes()) {
        return;
    }
    QCoreApplication::quit();
}
