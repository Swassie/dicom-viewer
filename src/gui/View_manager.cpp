#include "gui/View_manager.h"

#include <algorithm>
#include <cassert>
#include <QGridLayout>

void View_manager::set_view_factory(std::unique_ptr<View_factory> view_factory) {
    m_view_factory = std::move(view_factory);
}

void View_manager::set_view_count(const size_t count) {
    assert(m_view_factory);
    assert(count >= 1 && count <= 4);
    size_t current_count = m_views.size();
    if(count == current_count) {
        return;
    }
    delete layout();
    if(count > current_count) {
        for(size_t i = 0; i < count - current_count; ++i) {
            m_views.push_back(m_view_factory->make_default_view().release());
        }
    }
    else {
        for(size_t i = 0; i < current_count - count; ++i) {
            delete m_views.back();
            m_views.pop_back();
        }
    }
    create_layout();
}

void View_manager::show_default_layout() {
    assert(m_view_factory);
    for(auto view : m_views) {
        delete view;
    }
    m_views.clear();
    for(auto& view : m_view_factory->make_default_layout()) {
        m_views.push_back(view.release());
    }
    delete layout();
    create_layout();
}

void View_manager::replace_view(QWidget& old_view,
                                std::unique_ptr<QWidget> new_view) {
    assert(new_view.get());

    QLayout* layout = this->layout();
    assert(layout);

    QLayoutItem* layout_item = layout->replaceWidget(&old_view, new_view.get());
    assert(layout_item);
    delete layout_item;
    old_view.deleteLater();

    auto it = std::find(m_views.begin(), m_views.end(), &old_view);
    assert(it != m_views.end());
    *it = new_view.get();
    new_view.release();
}

void View_manager::create_layout() {
    switch(m_views.size()) {
    case 1:
        create_1_view_layout();
        break;
    case 2:
        create_2_view_layout();
        break;
    case 3:
        create_3_view_layout();
        break;
    case 4:
        create_4_view_layout();
        break;
    default:
        assert(false);
    }
}

void View_manager::create_1_view_layout() {
    QGridLayout* layout = new QGridLayout(this);
    layout->addWidget(m_views[0], 0, 0);
}

void View_manager::create_2_view_layout() {
    QGridLayout* layout = new QGridLayout(this);
    layout->addWidget(m_views[0], 0, 0);
    layout->addWidget(m_views[1], 0, 1);
    layout->setColumnStretch(0, 1);
    layout->setColumnStretch(1, 1);
}

void View_manager::create_3_view_layout() {
    QGridLayout* layout = new QGridLayout(this);
    layout->addWidget(m_views[0], 0, 0);
    layout->addWidget(m_views[1], 0, 1);
    layout->addWidget(m_views[2], 0, 2);
    layout->setColumnStretch(0, 1);
    layout->setColumnStretch(1, 1);
    layout->setColumnStretch(2, 1);
}

void View_manager::create_4_view_layout() {
    QGridLayout* layout = new QGridLayout(this);
    layout->addWidget(m_views[0], 0, 0);
    layout->addWidget(m_views[1], 0, 1);
    layout->addWidget(m_views[2], 1, 0);
    layout->addWidget(m_views[3], 1, 1);
    layout->setColumnStretch(0, 1);
    layout->setColumnStretch(1, 1);
    layout->setRowStretch(0, 1);
    layout->setRowStretch(1, 1);
}