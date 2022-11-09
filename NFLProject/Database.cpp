#include "Database.h"


QVector<Team> Database::getTeams()
{
	QVector<Team>allTeams;
	Team team;
	team.teamName = "Los Angeles Rams";
	team.stadium = "SoFi Stadium";
	team.capacity = "70000";
	team.location = "Inglewood";
	team.roofType = "Fixed";
	team.surface = "Hellas Matrix Turf";
	team.opened = "2020";
	team.conference = "National Football Conference";
	team.division = "NFC West";


	allTeams.push_back(team);

	return allTeams;
}
