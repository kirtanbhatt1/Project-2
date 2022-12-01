#pragma once

#include <QWidget>
#include "ui_PlanTrip.h"
#include "NFLProject.h"
#include "Graph.h"


class PlanTrip : public QWidget
{
	Q_OBJECT

public:
	PlanTrip(QWidget *parent = nullptr);
	~PlanTrip();

	void initializeEdges(QVector<Team> allCities);

	Graph getGraphCities();

	void depthFirstSearch();


private:
	Ui::PlanTripClass ui;
	Graph cities;
};
