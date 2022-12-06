#pragma once

#include <QWidget>
#include "ui_PlanTrip.h"
#include "NFLProject.h"
#include "Graph.h"
#include "W_TeamDistanceList.h"
#include "W_AddTeamSouvenirs.h"
#include "TeamToggle.h"
#include "Database.h"

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

	//void initializeEdges(QVector<Team> allCities);
	//Graph getGraphCities();
	//void depthFirstSearch();
	void open(TripMode mode);


private:
	Ui::PlanTripClass ui;
	Graph cities;

	TripMode tripMode;

	QVector<Stadium> stadiumsData;
	QVector<Distance> distancesData;

	// Both:
	void selectNumberOfTeams(int value);
	void teamSelected(int index);
	QString startingTeam = "";
	QVector<W_TeamDistanceList*> w_teamsList;
	void beginPlan();
	int totalDistance;

	// Shortest Plan
	void calculateShortestPlan(QString startingTeam, int teamsLeft);
	void addToTeamList(QString team, double distance);
	int numberOfTeams = 0;

	// Custom Plan
	QVector<TeamToggle*> w_TeamToggles;
	void addToCustomTeamList(QString team, double distance);
	QStringList selectedTeams;
	void teamToggled(bool value, QString team);
	void calculateCustomPlan(QString startingTeam, QVector<Distance>& distances);
	QStringList remainingTeams;

	// 2nd Menu:
	void switch2nd();
	QStringList plannedTeams; // A list in order of teams to go to
	QVector<W_AddTeamSouvenirs*> addedTeams;
	void totalPriceUpdated(double price); // Signal response for when a city's price for foods is updated.
	void triggerBack();

};
