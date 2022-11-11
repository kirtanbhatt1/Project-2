#pragma once
#include "NFLProject.h"
#include "Souvenir.h"

class Stadium
{

private:
	QString stadiumName;
	int capacity;
	QString location;
	QString roofType;
	QString surface;
	int openedYear;
	//vector to contain each stadium's different souvenirs (haven't put to use yet)
	QVector<Souvenir> souvenirs;

public:
	//default constructor
	Stadium()
		: stadiumName{ "" }, capacity{ 0 }, location{ "" }, roofType{ "" }, surface{ "" }, openedYear{ 0 } {}

	//overloaded constructor
	Stadium(QString stadiumName, int capacity, QString location, 
		    QString roofType, QString surface, int openedYear, 
		    QVector<Souvenir> allSouvenirs)
			: stadiumName{ stadiumName }, capacity{ capacity }, 
		      location{ location }, roofType{ roofType }, surface{ surface }, 
		      openedYear{ openedYear }, souvenirs{allSouvenirs} {}

	//destructor
	~Stadium() {}

	//getters
	QString getStadiumName()
	{
		return stadiumName;
	}

	int getCapacity()
	{
		return capacity;
	}

	QString getLocation()
	{
		return location;
	}

	QString getRoofType()
	{
		return roofType;
	}

	QString getSurface()
	{
		return surface;
	}

	int getOpenedYear()
	{
		return openedYear;
	}

	//setters
	void setStadiumName(QString stadiumName)
	{
		this->stadiumName = stadiumName;
	}

	void setCapacity(int capacity)
	{
		this->capacity = capacity;
	}

	void setLocation(QString location)
	{
		this->location = location;
	}

	void setRoofType(QString roofType)
	{
		this->roofType = roofType;
	}

	void setSurface(QString surface)
	{
		this->surface = surface;
	}

	void setOpenedYear(int openedYear)
	{
		this->openedYear = openedYear;
	}
};

