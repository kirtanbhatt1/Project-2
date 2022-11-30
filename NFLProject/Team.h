#pragma once
#include "NFLProject.h"
#include "Stadium.h"

class Team
{
private:
	QString teamName, teamConference, teamDivision;
	Stadium stadium;


public:
	Team() : teamName{""}, teamConference{""}, teamDivision{""}, stadium{} {}

	//compositional constructor for Team and Stadium together
	Team(QString teamName, QString teamConference, QString teamDivision,
		QString stadiumName, QString capacity, QString location, QString roofType,
		QString surface, int openedYear, QVector<Souvenir> allSouvenirs, QVector<Distance> allEdges)
		: teamName{ teamName }, teamConference{ teamConference }, teamDivision{ teamDivision },
		stadium{ stadiumName, capacity, location, roofType, surface, openedYear, allSouvenirs, allEdges } {}
	

	//getters & setters for Team
	QString getTeamName()
	{
		return teamName;
	}
	QString getConference()
	{
		return teamConference;
	}
	QString getDivision()
	{
		return teamDivision;
	}
	void setTeamName(QString name)
	{
		teamName = name;
	}
	void setConference(QString conference)
	{
		teamConference = conference;
	}
	void setDivision(QString division)
	{
		teamDivision = division;
	}

	void setStadiumSouvenirs(QVector<Souvenir> souvenirs){
		stadium.setSouvenirs(souvenirs);
	}

	void setStadiumEdges(QVector<Distance> edges) {
		stadium.setEdges(edges);
	}

	//getter for Stadium
	Stadium getStadium()
	{
		return stadium;
	}
	static bool compareConference(const Team& team1, const Team& team2) { return team1.teamConference < team2.teamConference; }
	static bool compareStadium( Team& team1,  Team& team2) { return team1.stadium.getStadiumName() < team2.stadium.getStadiumName(); }

};