#pragma once

#include <QMainWindow>
#include "ui_DisplayMST.h"
#include "Database.h"
#include "Dijkstra.h"
#include "W_DFSList.h"
#include "W_TotalCount.h"

class DisplayMST : public QMainWindow
{
	Q_OBJECT

public:
	DisplayMST(QWidget *parent = nullptr);
	~DisplayMST();
	void clearLayout();
	void showMST();

private:
	Ui::DisplayMSTClass ui;
	QVector<W_DFSList*> allWidgets;
	QVector<W_TotalCount*> countWidgets;
};
