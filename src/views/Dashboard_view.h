#pragma once
#include "views/IDashboard_view.h"

#include <QWidget>

class Dashboard_view : public QWidget, public IDashboard_view
{
    Q_OBJECT
public:
    Dashboard_view();
};
