#pragma once
#include "presenters/Main_presenter.h"

class Dicom_files;
class IMain_view;

class Main_editor_presenter : public Main_presenter
{
public:
    Main_editor_presenter(IMain_view&, Dicom_files&);

    void setup_event_handlers() override;
    void setup_view() override;

protected:
    void quit();

    IMain_view& m_view;
    Dicom_files& m_files;
};
