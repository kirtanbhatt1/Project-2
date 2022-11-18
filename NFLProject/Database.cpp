#include "Database.h"
#include <qDebug>


Database::Database(){
	NFLDatabase = QSqlDatabase::addDatabase("QSQLITE");
	NFLDatabase.setDatabaseName("C:/Users/knbha/source/repos/kirtanbhatt1/Project-2/SQLite/SQLite/NFLDatabase.db");
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
	db->exec("SELECT * FROM teamInfo");
	db2->exec("SELECT * FROM teamSouvenir");
	Map teamsMap;
	QVector<Souvenir> souvenirs;
	//Team team("Los Angeles Rams", "National Football Conference", "NFC West", "SoFi Stadium", 70000, "Inglewood, CA", "Fixed", "Hellas Matrix Turf", 2020, souvenirs );
	//allTeams.push_back(team);
	while (db->next()) {

		//SOUVENIRS IMPLEMENTATION
		////get team souvenior before it get added to team vector
		//QVector<Souvenir> souvenirs;
		//while (db2->next() && db2->value("teamName") != db->value("teamName")) {
		//	//qInfo() << db->value("city");
		//}
		//while (db2->next() && db2->value("teamName") != "") {
		//	QString name = db2->value("Souvenir").toString();
		//	double price = db2->value("souvenirPrice").toDouble();
		//	Souvenir* temp = new Souvenir(name, price);
		//	qDebug() << "Hello world";//db->value("teamName") << "\t" << name << "\t" << price;
		//	souvenirs.push_back(temp);
		//}

		//add team info to the vector
		Team* currentTeam = new Team(db->value("teamName").toString(), db->value("conference").toString(), db->value("division").toString(), db->value("stadium").toString(), db->value("capacity").toString(),
			db->value("location").toString(), db->value("rooftype").toString(), db->value("surface").toString(), db->value("opened").toInt(), souvenirs);
		teamsMap.insert(currentTeam->getTeamName(), *currentTeam);
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
