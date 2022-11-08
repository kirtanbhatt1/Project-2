#pragma once
#include "NFLProject.h"

class Stadium
{

private:
	QString stadiumName;
	int capacity;
	QString location;
	QString roofType;
	QString surface;
	int openedYear;

public:
	//constructor
	Stadium();
	Stadium(QString stadiumName, int capacity, QString location, QString roofType, QString surface, int openedYear);

	//destructor
	~Stadium();

	//getters
	QString getStadiumName();
	int getCapacity();
	QString getLocation();
	QString getRoofType();
	QString getSurface();
	int getOpenedYear();

	//setters
	void setStadiumName(QString stadiumName);
	void setCapacity(int capacity);
	void setLocation(QString location);
	void setRoofType(QString roofType);
	void setSurface(QString surface);
	void setOpenedYear(int openedYear);
};