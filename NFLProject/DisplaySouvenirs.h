#pragma once

#include <QMainWindow>
#include "ui_DisplaySouvenirs.h"
#include "W_SouvenirList.h"

class DisplaySouvenirs : public QMainWindow
{
	Q_OBJECT

public:
	DisplaySouvenirs(QWidget *parent = nullptr);
	~DisplaySouvenirs();
	void displayAllSouvenirs();
	void clearLayout();
	void initializeList();
	void open();

private:
	Ui::DisplaySouvenirsClass ui;
	QVector<W_SouvenirList*> allWidgets;
};
