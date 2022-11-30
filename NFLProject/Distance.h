#pragma once
#include "NFLProject.h"
#include "Souvenir.h"


class Distance
{
private:
	QString startingStadium;
	QString endingStadium;
	int distance;

public:
	Distance()
		: startingStadium(""), endingStadium(" "), distance(0) {}
	Distance(QString startingStadium, QString endingStadium, int distance)
		: startingStadium{startingStadium}, endingStadium{ endingStadium }, distance{ distance } {}
	~Distance() {}
	void setStartingStadium(QString stadiumName)
	{
		startingStadium = stadiumName;
	}
	void setEndingStadium(QString stadiumName)
	{
		endingStadium = stadiumName;
	}
	void setDistance(int dist)
	{
		distance = dist;
	}
	
	QString getStartingStadium()
	{
		return startingStadium;
	}

	QString getEndingStadium()
	{
		return endingStadium;
	}
	int getDistance()
	{
		return distance;
	}
};