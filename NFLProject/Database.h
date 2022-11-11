#pragma once
#include "NFLProject.h"
//#include "Map.h"
#include "Team.h"
#include "Stadium.h"
#include "qvector.h"
#include <iostream>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>

class Database
{
public:
	QSqlDatabase NFLDatabase;
	//Map<QString, Team> teams;
	Database();
	~Database();
	QVector<Team> getTeams();
};