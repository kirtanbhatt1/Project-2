#pragma once
#include "NFLProject.h"
#include "Map.h"
#include "Team.h"
#include "Stadium.h"
#include "Distance.h"
#include "qvector.h"
#include <iostream>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
//#include "NewDistance.h"

class Database
{
public:
	QSqlDatabase NFLDatabase;

	QVector<Distance> distances;
	QVector<NewDistance> newdistances;

	//Map teams;
	Database();
	~Database();
	QVector<Team> getTeams();
	Map initializeMap();
	long getTotalCapacity(QVector<Team> teams);
	Team getTeam(QString teamName);
	static QVector<Distance> getAllDistances();

	QVector<Stadium> getAllStadiums();
};