#pragma once

#include <QMainWindow>
#include "ui_DisplayDFS.h"
#include "PlanTrip.h"
#include "W_DFSList.h"
#include "QFileDialog.h"

class DisplayDFS : public QMainWindow
{
	Q_OBJECT

public:
	DisplayDFS(QWidget *parent = nullptr);
	~DisplayDFS();
	void clearLayout();
	void showDFS();

	Ui::DisplayDFSClass ui;
	QVector<W_DFSList*> allWidgets;

};
