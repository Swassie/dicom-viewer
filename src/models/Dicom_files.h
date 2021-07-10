#pragma once
#include "common/Event.h"
#include "Dicom_file.h"

#include <memory>
#include <vector>

class Dicom_files
{
public:
    Event<> files_added_event;

    void add_files(std::vector<std::unique_ptr<Dicom_file>>);
    bool has_unsaved_changes() const;

protected:
    std::vector<std::unique_ptr<Dicom_file>> m_files;
};
