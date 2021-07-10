#include "dcmedit.h"

#include "logging/Log.h"
#include "models/Dicom_files.h"
#include "presenters/Main_dashboard_presenter.h"
#include "presenters/Main_editor_presenter.h"
#include "presenters/Open_files_presenter.h"
#include "views/About_view.h"
#include "views/Main_view.h"
#include "views/Open_files_view.h"
#include "views/Dashboard_view.h"

#include <QApplication>

dcmedit::dcmedit()
    : m_main_presenter_state(Main_presenter_t::invalid),
      m_main_dashboard_presenter(nullptr),
      m_main_editor_presenter(nullptr) {}

int dcmedit::run(int argc, char** argv) {
    QApplication app(argc, argv);
    app.setApplicationName("dcmedit");

    Dicom_files dicom_files;

    // Setup GUI.
    auto dashboard_view = new Dashboard_view();

    Main_view main_view{std::unique_ptr<Dashboard_view>(dashboard_view)};
    Main_dashboard_presenter main_dashboard_presenter(main_view);
    Main_editor_presenter main_editor_presenter(main_view, dicom_files);
    m_main_dashboard_presenter = &main_dashboard_presenter;
    m_main_editor_presenter = &main_editor_presenter;
    setup_dashboard_presenter();

    Open_files_view open_files_view(&main_view);
    Open_files_presenter open_files_presenter(open_files_view, dicom_files);

    About_view about_view(&main_view);

    // Add event handlers.
    dashboard_view->open_files_event.add_handler([&] {open_files_presenter.open_files();});
    main_view.open_files_event.add_handler([&] {open_files_presenter.open_files();});
    main_view.about_event.add_handler([&] {about_view.show_about_dialog();});
    dicom_files.files_added_event.add_handler([this] {files_added();});

    main_view.show();

    return app.exec();
}

void dcmedit::setup_dashboard_presenter() {
    m_main_editor_presenter->remove_event_handlers();
    m_main_dashboard_presenter->setup_event_handlers();
    m_main_dashboard_presenter->setup_view();
    m_main_presenter_state = Main_presenter_t::dashboard;
}

void dcmedit::setup_editor_presenter() {
    Log::info("Changing to editor.");
}

void dcmedit::files_added() {
    if(m_main_presenter_state == Main_presenter_t::dashboard) {
        setup_editor_presenter();
    }
}
