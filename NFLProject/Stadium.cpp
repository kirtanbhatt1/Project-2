#include "Stadium.h"

Stadium::Stadium() : stadiumName{""}, capacity{0}, location{""}, roofType{""}, surface{""}, openedYear{0} {}

Stadium::Stadium(QString stadiumName, int capacity, QString location, QString roofType, QString surface, int openedYear) : stadiumName{stadiumName}, capacity{capacity}, location{location}, roofType{roofType}, surface{surface}, openedYear{openedYear} {}

Stadium::~Stadium() {}

QString Stadium::getStadiumName()
{
	return stadiumName;
}

int Stadium::getCapacity()
{
	return capacity;
}

QString Stadium::getLocation()
{
	return location;
}

QString Stadium::getRoofType()
{
	return roofType;
}

QString Stadium::getSurface()
{
	return surface;
}

int Stadium::getOpenedYear()
{
	return openedYear;
}

void Stadium::setStadiumName(QString stadiumName)
{
	this->stadiumName = stadiumName;
}

void Stadium::setCapacity(int capacity)
{
	this->capacity = capacity;
}

void Stadium::setLocation(QString location)
{
	this->location = location;
}

void Stadium::setRoofType(QString roofType)
{
	this->roofType = roofType;
}

void Stadium::setSurface(QString surface)
{
	this->surface = surface;
}

void Stadium::setOpenedYear(int openedYear)
{
	this->openedYear = openedYear;
}