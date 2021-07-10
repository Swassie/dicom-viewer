#include "models/Dicom_files.h"

#include "Dicom_file.h"

#include <algorithm>

void Dicom_files::add_files(std::vector<std::unique_ptr<Dicom_file>> files) {
    if(files.empty()) {
        return;
    }
    for(auto& new_file : files) {
        auto new_file_path = new_file->get_path();
        bool duplicate_file = false;
        for(auto& file : m_files) {
            if(file->get_path() == new_file_path) {
                duplicate_file = true;
                break;
            }
        }
        if(!duplicate_file) {
            m_files.push_back(std::move(new_file));
        }
    }
    files_added_event.trigger();
}

bool Dicom_files::has_unsaved_changes() const {
    return std::any_of(m_files.begin(), m_files.end(), [] (auto& file) {
        return file->has_unsaved_changes();
    });
}
