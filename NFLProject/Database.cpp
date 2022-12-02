#include "Database.h"
#include <qDebug>


Database::Database(){
	NFLDatabase = QSqlDatabase::addDatabase("QSQLITE");
	NFLDatabase.setDatabaseName("C:/Users/remos/Project-2/SQLite/SQLite/NFLDatabase.db");
	NFLDatabase.open();
	if (NFLDatabase.open()) {
		std::cout << "Database is open\n";
	}
	else {
		std::cout << "Database is not open\n";
	}
}

Database::~Database(){

}

Map Database::initializeMap()
{
	QSqlQuery* db = new QSqlQuery(NFLDatabase);
	QSqlQuery* db2 = new QSqlQuery(NFLDatabase);
	QSqlQuery* db3 = new QSqlQuery(NFLDatabase);
	db->exec("SELECT * FROM teamInfo");
	db2->exec("SELECT * FROM teamSouvenir");
	db3->exec("SELECT * FROM teamDistance");

	Map teamsMap;
	//Team team("Los Angeles Rams", "National Football Conference", "NFC West", "SoFi Stadium", 70000, "Inglewood, CA", "Fixed", "Hellas Matrix Turf", 2020, souvenirs );
	//allTeams.push_back(team);
	while (db->next()) {

		// SOUVENIRS IMPLEMENTATION
		// get team souvenior before it get added to team vector
		QVector<Souvenir> souvenirs;
		while (db2->next() && db2->value("teamName") != db->value("teamName")) {
			//qInfo() << db->value("city");
		}
		while (db2->next() && db2->value("teamName") == "") {
				QString name = db2->value("Souvenir").toString();
				double price = db2->value("souvenirPrice").toDouble();
				Souvenir* temp = new Souvenir(name, price);
				souvenirs.push_back(*temp);
		}

		QVector<Distance> edges;
		while (db3->next() && db3->value("teamName") != db->value("teamName")) {
			//qInfo() << db->value("city");
		}
		while (db3->next() && db3->value("teamName") == "") {

			QString startingStadiumName = db3->value("beginningStadium").toString();
			QString endingStadiumName = db3->value("endingStadium").toString();
			int distance = db3->value("Distance").toInt();
			//qDebug() << "START: " << startingStadiumName << "END: " << endingStadiumName << "DISTANCE: " << distance;
			Distance* temp = new Distance(startingStadiumName, endingStadiumName, distance);
			edges.push_back(*temp);
		}

		// add team info to the vector
		Team* currentTeam = new Team(db->value("teamName").toString(), db->value("conference").toString(), db->value("division").toString(), db->value("stadium").toString(), db->value("capacity").toString(),
			db->value("location").toString(), db->value("rooftype").toString(), db->value("surface").toString(), db->value("opened").toInt(), souvenirs, edges);
		teamsMap.insert(currentTeam->getTeamName(), *currentTeam);
		db2->seek(0);
		db3->seek(0);
	}

	return teamsMap;
}

QVector<Team> Database::getTeams()
{
	Map teamMap = initializeMap();
	QVector<Team> teams;

	for (int i = 0; i < teamMap.size(); i++)
	{
		teams.push_back(teamMap[i]);
	}

	return teams;
}

long Database::getTotalCapacity(QVector<Team> teams)
{
	long totalCapacity = 0;

	for (int i = 0; i < teams.size(); i++)
	{
		totalCapacity += teams[i].getStadium().getCapacity().toLong();
		qDebug() << teams[i].getTeamName() << " has capacity: " << teams[i].getStadium().getCapacity();
		qDebug() << "total Capacity: " << totalCapacity;
	}
	return totalCapacity;
}

Team Database::getTeam(QString teamName)
{
	Database database;

	QVector<Team> teams = database.getTeams();
	Team teamData;

	for (int i = 0; i < teams.size(); i++)
	{
		if (teams[i].getTeamName() == teamName)
		{
			teamData = teams[i];
		}
	}
	return teamData;
}

QVector<Distance> Database::getAllDistances()
{
	QVector<Distance> distances;
	QSqlQuery query;
	query.prepare("SELECT StartingCity, EndingCity, Kilometers FROM distances");

	if (query.exec())
	{
		while (query.next())
		{
			Distance distance;
			distance.getStartingStadium() = query.value(0).toString();
			distance.getEndingStadium() = query.value(1).toString();
			//distance.getDistance() = query.value(2);

			qInfo() << query.value(2);

			distances.push_back(distance);
		}
	}
	return distances;
}