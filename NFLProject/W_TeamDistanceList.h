#pragma once

#include <QWidget>
#include "ui_W_TeamDistanceList.h"

class W_TeamDistanceList : public QWidget
{
	Q_OBJECT

public:
	W_TeamDistanceList(QWidget *parent = nullptr);
	~W_TeamDistanceList();
	void setup(QString team, long distance);
	void setup(QString startingTeam);

	QString team;
	long distance;

private:
	Ui::W_TeamDistanceListClass ui;
};
