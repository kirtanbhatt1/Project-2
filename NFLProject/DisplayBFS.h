#pragma once

#include <QMainWindow>
#include "ui_DisplayBFS.h"
#include "PlanTrip.h"
#include "W_BFSList.h"
#include "W_TotalCount.h"
#include "qfiledialog.h"

class DisplayBFS : public QMainWindow
{
	Q_OBJECT

public:
	DisplayBFS(QWidget *parent = nullptr);
	~DisplayBFS();
	void clearLayout();
	void showBFS();

private:
	Ui::DisplayBFSClass ui;
	QVector<W_BFSList*> allWidgets;
	QVector<W_TotalCount*> allCountWidgets;

};
