#pragma once

#include <QMainWindow>
#include "ui_DisplaySorted.h"
#include "Database.h"

class DisplaySorted : public QMainWindow
{
	Q_OBJECT

public:
	DisplaySorted(QWidget *parent = nullptr);
	~DisplaySorted();



private:
	Ui::DisplaySortedClass ui;
};
