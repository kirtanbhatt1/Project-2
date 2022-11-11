#include "Database.h"


QVector<Team> Database::getTeams()
{
	QVector<Team>allTeams;
	QVector<Souvenir> souvenirs;
	Team team("Los Angeles Rams", "National Football Conference", "NFC West", "SoFi Stadium", 70000, "Inglewood, CA", "Fixed", "Hellas Matrix Turf", 2020, souvenirs );
	allTeams.push_back(team);

	return allTeams;
}
