#pragma once

#include <QMainWindow>
#include "ui_Plan.h"
#include "NFLProject.h"
#include "Graph.h"

class Plan : public QMainWindow
{
	Q_OBJECT

public:
	Plan(QWidget *parent = nullptr);
	~Plan();

	void initializeEdges(QVector<Team> allCities);

	Graph getGraph();

private:
	Ui::PlanClass ui;
	Graph cities;
};
