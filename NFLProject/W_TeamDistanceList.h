#pragma once

#include <QWidget>
#include "ui_W_TeamDistanceList.h"

class W_TeamDistanceList : public QWidget
{
	Q_OBJECT

public:
	W_TeamDistanceList(QWidget *parent = nullptr);
	~W_TeamDistanceList();
	void setup(QString team, double distance);
	void setup(QString startingTeam);

	QString team;
	double distance;

private:
	Ui::W_TeamDistanceListClass ui;
};
