#pragma once

#include <QMainWindow>
#include "ui_W_DistanceList.h"

class W_DistanceList : public QMainWindow
{
	Q_OBJECT

public:
	W_DistanceList(QWidget *parent = nullptr);
	~W_DistanceList();
	void setup(QString startingStadium, QString endingStadium, int distance);

private:
	Ui::W_DistanceListClass ui;
};
