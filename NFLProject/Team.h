#pragma once
#include "NFLProject.h"
#include "Stadium.h"

class Team
{
private:
	QString teamName, teamConference, teamDivision;
	Stadium stadium;

public:
	//compositional constructor for Team and Stadium together
	Team(QString teamName, QString teamConference, QString teamDivision,
		QString stadiumName, int capacity, QString location, QString roofType,
		QString surface, int openedYear, QVector<Souvenir> allSouvenirs)
		: teamName{ teamName }, teamConference{ teamConference }, teamDivision{ teamDivision },
		stadium{ stadiumName, capacity, location, roofType, surface, openedYear, allSouvenirs } {}
	

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

	//getter for Stadium
	Stadium getStadium()
	{
		return stadium;
	}

};
