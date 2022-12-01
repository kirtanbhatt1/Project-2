#pragma once

#include <QWidget>
#include "ui_PlanTrip.h"
#include "NFLProject.h"
#include "Graph.h"
#include "W_TeamDistanceList.h"

enum TripMode 
{
	shortest = 1,
	custom = 2,
};


class PlanTrip : public QWidget
{
	Q_OBJECT

public:
	PlanTrip(QWidget *parent = nullptr);
	~PlanTrip();

	void initializeEdges(QVector<Team> allCities);
	Graph getGraphCities();
	void depthFirstSearch();
	void open(TripMode mode);


private:
	Ui::PlanTripClass ui;
	Graph cities;

	TripMode tripMode;

	QVector<Team> teamData;
	QVector<Distance> distancesData;

	// Both:
	void selectNumberOfCities(int value);
	void citySelected(int index);
	QString startingTeam = "";
	QVector<W_TeamDistanceList*> w_teamsList;
	void beginPlan();
	int totalDistance;

	// Shortest Plan
	void calculateShortestPlan(QString startingTeam, int teamsLeft);
	void addToTeamList(QString team, double distance);
	int numberOfTeams = 0;

	//// Custom Plan
	//QVector<CityToggle*> w_CityToggles;
	//void addToCustomCityList(QString city, double distance);
	//QStringList selectedCities;
	//void cityToggled(bool value, QString city);
	//void calculateCustomPlan(QString startingCity, QVector<Distance>& distances);
	//QStringList remainingCities;

	// 2nd Menu:
	// void switch2nd();
	QStringList plannedTeams; // A list in order of cities to go to
	//QVector<W_AddTeamSouvenirs*> addedCities;
	//void totalPriceUpdated(double price); // Signal response for when a city's price for foods is updated.
	void triggerBack();

};
