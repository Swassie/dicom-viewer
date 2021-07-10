#pragma once

class Main_dashboard_presenter;
class Main_editor_presenter;

class dcmedit
{
    enum class Main_presenter_t {
        dashboard,
        editor,
        invalid
    };

public:
    dcmedit();

    int run(int argc, char** argv);

protected:
    void setup_dashboard_presenter();
    void setup_editor_presenter();

    void files_added();

    Main_presenter_t m_main_presenter_state;
    Main_dashboard_presenter* m_main_dashboard_presenter;
    Main_editor_presenter* m_main_editor_presenter;
};
