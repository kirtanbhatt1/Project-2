#pragma once

#include <QWidget>
#include "ui_W_TeamsList.h"

class W_TeamsList : public QWidget
{
	Q_OBJECT

public:
	W_TeamsList(QWidget *parent = nullptr);
	~W_TeamsList();
	void setup(QString teamName, QString stadium, QString capacity, QString location,
		QString roofType, QString surface, QString conference, QString opened, QString division);


private:
	Ui::W_TeamsListClass ui;
};
