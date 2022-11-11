#include "Database.h"


Database::Database(){
	NFLDatabase = QSqlDatabase::addDatabase("QSQLITE");
	NFLDatabase.setDatabaseName("C:/Users/nicho/Desktop/CS1D Proj2/Project-2/SQLite/SQLite/NFLDatabase.db");
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

QVector<Team> Database::getTeams()
{
	QSqlQuery* db = new QSqlQuery(NFLDatabase);
	QSqlQuery* db2 = new QSqlQuery(NFLDatabase);
	db->exec("SELECT * FROM teamInfo");
	db2->exec("SELECT * FROM teamSouvenir");
	QVector<Team>allTeams;
	QVector<Souvenir> souvenirs;
	//Team team("Los Angeles Rams", "National Football Conference", "NFC West", "SoFi Stadium", 70000, "Inglewood, CA", "Fixed", "Hellas Matrix Turf", 2020, souvenirs );
	//allTeams.push_back(team);
	while (db->next()){
		//add team info to the vector
		Team* currentTeam = new Team(db->value("teamName").toString(), db->value("conference").toString(), db->value("division").toString(), db->value("stadium").toString(), db->value("capacity").toString(), 
		db->value("location").toString(), db->value("rooftype").toString(), db->value("surface").toString(), db->value("opened").toInt(), souvenirs);
		allTeams.push_back(*currentTeam);
	}

	//for (int i = 0; i < allTeams.size(); i++) {
	//	while (db2->value("teamName") != allTeams[i].getTeamName() && db2->next()) {
	//	}
	//	while (db2->next()) {
	//		Souvenir* product = new Souvenir(db2->value("Souvenir").toString(), db2->value("souvenirPrice").toDouble());
	//		souvenirs.push_back(*product);
	//	}
	//	allTeams[i].setStadiumSouvenirs(souvenirs);
	//	souvenirs.erase(souvenirs.begin(), souvenirs.end());
	//}
	//for(int i = 0; i < allTeams.size(); i++){
	//	QVector<Souvenir> current = allTeams[i].getStadium().getSouvenirs();
	//	for (int j = 0; i < current.size(); j++) {
	//	qInfo() << current[j].getName() << "\t" << current[j].getPrice() << "\n";
	//	}
	//	//std::cout << std::endl;
	//}
	return allTeams;
}

            ////read team souvenir
            //while(!stream14.atEnd()){
            //    SteamName = stream14.readLine();
            //    qInfo() << "Teamname: " << SteamName;

            //    QFile Ss("C:/Users/Eric0/Desktop/Project 2/souvenir.txt");
            //    QFile Sp("C:/Users/Eric0/Desktop/Project 2/souvenirPrice.txt");
            //    Ss.open(QIODevice::OpenModeFlag::ReadOnly);
            //    Sp.open(QIODevice::OpenModeFlag::ReadOnly);
            //    QTextStream stream15(&Ss);
            //    QTextStream stream16(&Sp);

            //    db->prepare("insert into teamSouvenir (teamName, Souvenir, souvenirPrice) values ('"+SteamName+"','""','""')");
            //    db->exec();

            //    while(!stream15.atEnd()){
            //        Ssouvenir = stream15.readLine();
            //        Sprice = stream16.readLine();
            //        qInfo() << Ssouvenir << " " << Sprice;

            //        db->prepare("insert into teamSouvenir (teamName, Souvenir, souvenirPrice) values ('""','"+Ssouvenir+"','"+Sprice+"')");
            //        db->exec();

            //        stream15.reset();
            //        stream16.reset();
            //    }
			//}
