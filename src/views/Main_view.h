#pragma once
#include "views/IMain_view.h"
#include "views/Dashboard_view.h"

#include <memory>
#include <QMainWindow>

class Main_view : public QMainWindow, public IMain_view
{
    Q_OBJECT
public:
    Main_view(std::unique_ptr<Dashboard_view>);

    void set_dashboard_view() override;
    void set_editor_view() override;

    void set_window_modified(bool) override;
    void set_window_title(const QString&) override;

    bool is_ok_to_discard_changes() override;

protected:
    void closeEvent(QCloseEvent*) override;

    std::unique_ptr<Dashboard_view> m_dashboard_view;
};
