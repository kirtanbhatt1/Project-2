#pragma once

#include <QMainWindow>
#include "ui_DisplayDFS.h"
#include "PlanTrip.h"

class DisplayDFS : public QMainWindow
{
	Q_OBJECT

public:
	DisplayDFS(QWidget *parent = nullptr);
	~DisplayDFS();
	void showDFS();

	Ui::DisplayDFSClass ui;
};
