#pragma once

#include <QWidget>
#include "ui_W_TeamsList.h"
//#include "NFLProject.h"
//#include "Database.h"
//#include "Map.h"
//#include "Souvenir.h"
//#include "Stadium.h"
//#include "Team.h"

class W_TeamsList : public QWidget
{
	Q_OBJECT

public:
	W_TeamsList(QWidget *parent = nullptr);
	~W_TeamsList();
	void setup(QString teamName, QString stadium, QString capacity, QString location,
		QString roofType, QString surface, QString conference, int opened, QString division);


private:
	Ui::W_TeamsListClass ui;
};
