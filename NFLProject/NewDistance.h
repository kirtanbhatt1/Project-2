#pragma once
#include "NFLProject.h"
#include "Souvenir.h"


class NewDistance
{
public:

	QString startingTeam;
	QString endingTeam;
	int distance;


	NewDistance()
		: startingTeam(""), endingTeam(" "), distance(0) {}
	NewDistance(QString startingTeam, QString endingTeam, int distance)
		: startingTeam{ startingTeam }, endingTeam{ endingTeam }, distance{ distance } {}
	~NewDistance() {}
	void setStartingTeam(QString stadiumName)
	{
		startingTeam = stadiumName;
	}
	void setEndingTeam(QString stadiumName)
	{
		endingTeam = stadiumName;
	}
	void setDistance(int dist)
	{
		distance = dist;
	}

	QString getstartingTeam()
	{
		return startingTeam;
	}

	QString getendingTeam()
	{
		return endingTeam;
	}
	int getDistance()
	{
		return distance;
	}
};