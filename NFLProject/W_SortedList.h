#pragma once

#include <QWidget>
#include "ui_W_SortedList.h"

class W_SortedList : public QWidget
{
	Q_OBJECT

public:
	W_SortedList(QWidget *parent = nullptr);
	~W_SortedList();
	void setup(QString teamName, QString stadium, QString capacity, QString location,
		QString roofType, QString surface, QString conference, int opened, QString division);

private:
	Ui::W_SortedListClass ui;
};
