#pragma once
#include "NFLProject.h"
#include "Map.h"
#include "Team.h"
#include "Stadium.h"
#include "qvector.h"

class Database
{
public:
	static QVector<Team> getTeams();
};