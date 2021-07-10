#include "views/Main_view.h"

#include <QCloseEvent>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>

Main_view::Main_view(std::unique_ptr<Dashboard_view> dashboard_view)
    : m_dashboard_view(std::move(dashboard_view)) {
    setMinimumSize(800, 600);
}

void Main_view::set_dashboard_view() {
    auto menu_bar = new QMenuBar(this);

    auto file_menu = new QMenu("&File", menu_bar);
    file_menu->addAction("Open files", [this] {open_files_event.trigger();}, QKeySequence::Open);
    file_menu->addAction("Quit", [this] {quit_event.trigger();}, QKeySequence::Quit);
    menu_bar->addMenu(file_menu);

    auto help_menu = new QMenu("&Help", menu_bar);
    help_menu->addAction("About", [this] {about_event.trigger();});
    menu_bar->addMenu(help_menu);

    setMenuBar(menu_bar);

    takeCentralWidget();
    setCentralWidget(m_dashboard_view.get());
}

void Main_view::set_editor_view() {
    auto menu_bar = new QMenuBar(this);

    auto file_menu = new QMenu("&File", menu_bar);
    file_menu->addAction("Open files", [this] {open_files_event.trigger();}, QKeySequence::Open);
    file_menu->addAction("Save file", [this] {save_file_event.trigger();}, QKeySequence::Save);
    file_menu->addAction("Save file as", [this] {save_file_as_event.trigger();}, QKeySequence::SaveAs);
    file_menu->addAction("Save all files", [this] {save_all_files_event.trigger();});
    file_menu->addAction("Clear all files", [this] {clear_all_files_event.trigger();});
    file_menu->addAction("Quit", [this] {quit_event.trigger();}, QKeySequence::Quit);
    menu_bar->addMenu(file_menu);

    auto view_menu = new QMenu("&View", menu_bar);
    view_menu->addAction("1 view", [this] {set_view_count_event.trigger(1);}, QKeySequence("Ctrl+1"));
    view_menu->addAction("2 views", [this] {set_view_count_event.trigger(2);}, QKeySequence("Ctrl+2"));
    view_menu->addAction("3 views", [this] {set_view_count_event.trigger(3);}, QKeySequence("Ctrl+3"));
    view_menu->addAction("4 views", [this] {set_view_count_event.trigger(4);}, QKeySequence("Ctrl+4"));
    view_menu->addSeparator();
    menu_bar->addMenu(view_menu);

    auto help_menu = new QMenu("&Help", menu_bar);
    help_menu->addAction("About", [this] {about_event.trigger();});
    menu_bar->addMenu(help_menu);

    setMenuBar(menu_bar);

    takeCentralWidget();
    setCentralWidget(m_dashboard_view.get());
}

void Main_view::set_window_modified(bool modified) {
    setWindowModified(modified);
}

void Main_view::set_window_title(const QString& title) {
    setWindowTitle(title);
}

void Main_view::closeEvent(QCloseEvent* event) {
    event->ignore();
    quit_event.trigger();
}

bool Main_view::is_ok_to_discard_changes() {
    auto answer = QMessageBox::question(this, "Discard unsaved changes?",
                                        "Do you really want to discard unsaved changes?");
    return answer == QMessageBox::Yes;
}
