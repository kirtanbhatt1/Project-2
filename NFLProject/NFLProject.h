#pragma once

#include <QtWidgets/QMainWindow>
#include <qfontdatabase.h>
#include <qfont.h>
#include "ui_NFLProject.h"

class NFLProject : public QMainWindow
{
    Q_OBJECT

public:
    NFLProject(QWidget *parent = nullptr);
    ~NFLProject();

private:
    Ui::NFLProjectClass ui;
};