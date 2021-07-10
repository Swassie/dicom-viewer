cmake_minimum_required(VERSION 3.10)
project(dcmedit)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(DCMTK REQUIRED)

add_executable(dcmedit
  assets/assets.qrc
  src/dcmedit.cpp
  src/dcmedit.h
  src/Dicom_file.cpp
  src/Dicom_file.h
  src/Dicom_util.cpp
  src/Dicom_util.h
  src/Version.cpp
  src/Version.h
  src/common/Event.h
  src/common/Event_handler_list.cpp
  src/common/Event_handler_list.h
  src/models/Dicom_files.cpp
  src/models/Dicom_files.h
  src/gui/Dataset_model.cpp
  src/gui/Dataset_model.h
  src/gui/File_tree.cpp
  src/gui/File_tree.h
  src/gui/Gui_util.h
  src/gui/Main_window.cpp
  src/gui/Main_window.h
  src/gui/Start_screen.cpp
  src/gui/Start_screen.h
  src/gui/View_factory.cpp
  src/gui/View_factory.h
  src/gui/View_manager.cpp
  src/gui/View_manager.h
  src/gui/dialog/Batch_dialog.cpp
  src/gui/dialog/Batch_dialog.h
  src/gui/menu/Menu.cpp
  src/gui/menu/Menu.h
  src/gui/menu/Tool_bar.cpp
  src/gui/menu/Tool_bar.h
  src/gui/studio/Dicom_studio.cpp
  src/gui/studio/Dicom_studio.h
  src/gui/studio/Start_studio.cpp
  src/gui/studio/Start_studio.h
  src/gui/studio/Studio.h
  src/gui/tool/Tool.h
  src/gui/tool/Transform_tool.cpp
  src/gui/tool/Transform_tool.h
  src/gui/view/Add_element_dialog.cpp
  src/gui/view/Add_element_dialog.h
  src/gui/view/Dataset_view.cpp
  src/gui/view/Dataset_view.h
  src/gui/view/Edit_element_dialog.cpp
  src/gui/view/Edit_element_dialog.h
  src/gui/view/Image_view.cpp
  src/gui/view/Image_view.h
  src/gui/view/View.cpp
  src/gui/view/View.h
  src/logging/Console_logger.cpp
  src/logging/Console_logger.h
  src/logging/Log.cpp
  src/logging/Log.h
  src/logging/Logger.h
  src/presenters/Main_presenter.cpp
  src/presenters/Main_presenter.h
  src/presenters/Main_dashboard_presenter.cpp
  src/presenters/Main_dashboard_presenter.h
  src/presenters/Main_editor_presenter.cpp
  src/presenters/Main_editor_presenter.h
  src/presenters/Open_files_presenter.cpp
  src/presenters/Open_files_presenter.h
  src/views/About_view.cpp
  src/views/About_view.h
  src/views/IAbout_view.h
  src/views/IMain_view.h
  src/views/IOpen_files_view.h
  src/views/IDashboard_view.h
  src/views/Main_view.cpp
  src/views/Main_view.h
  src/views/Open_files_view.cpp
  src/views/Open_files_view.h
  src/views/Dashboard_view.cpp
  src/views/Dashboard_view.h
  src/main.cpp
)

set_property(SOURCE src/Version.cpp PROPERTY SKIP_AUTOGEN ON)

add_custom_command(
  OUTPUT "${CMAKE_SOURCE_DIR}/src/Version.cpp" phony_output
  COMMAND "${CMAKE_COMMAND}" -P "${CMAKE_SOURCE_DIR}/version.cmake"
  WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
  VERBATIM)

set_target_properties(dcmedit PROPERTIES CXX_STANDARD 17)
target_compile_options(dcmedit PRIVATE -Wall -Wextra -pedantic)

target_include_directories(dcmedit PRIVATE
  src
  "${DCMTK_INCLUDE_DIRS}"
)

target_link_libraries(dcmedit
  Qt5::Widgets
  "${DCMTK_LIBRARIES}"
)

add_subdirectory(test)
