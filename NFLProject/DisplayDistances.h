#pragma once

#include <QMainWindow>
#include "ui_DisplayDistances.h"
#include "W_DistanceList.h"

class DisplayDistances : public QMainWindow
{
	Q_OBJECT

public:
	DisplayDistances(QWidget *parent = nullptr);
	~DisplayDistances();
	void displayAllDistances();
	void clearLayout();
	void initializeList();
	void open();

private:
	Ui::DisplayDistancesClass ui;
	QVector<W_DistanceList*> allWidgets;
};
