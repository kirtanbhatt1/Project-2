#pragma once
#include "NFLProject.h"
#include <QtCore>

class Souvenir
{
private:
	QString name;
	double price;

public:

	int amount;

	Souvenir() : name{ "" }, price{ 0 } {}

	//default constructor
	Souvenir(QString souvenirName, double souvenirPrice)
		: name{ souvenirName }, price{ souvenirPrice } {}

	//destructor 
	~Souvenir() {}

	// getters & setters
	void setSouvenirName(QString souvenirName)
	{
		name = souvenirName;
	}

	void setPrice(double souvenirPrice)
	{
		price = souvenirPrice;
	}

	QString getName()
	{
		return name;
	}
	double getPrice()
	{
		return price;
	}

	double getTotal()
	{
		return price * amount;
	}
};