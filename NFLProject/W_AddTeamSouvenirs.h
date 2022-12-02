#pragma once

#include <QWidget>
#include "ui_W_AddTeamSouvenirs.h"
#include "Database.h"
#include <vector>
#include "Team.h"
#include "W_NewSouvenir.h"
#include "W_SelectSouvenir.h"

class W_AddTeamSouvenirs : public QWidget
{
	Q_OBJECT

public:
	W_AddTeamSouvenirs(QWidget *parent = nullptr);
	~W_AddTeamSouvenirs();
	void setup(Team team);
	double getTotal();
	int numOfPurchases();

signals: 
	void priceUpdated(double price);

private:
	Ui::W_AddTeamSouvenirsClass ui;
	QVector<Souvenir> availableSouvenirs;
	QStack<Souvenir> addedSouvenirs; // List of souvenirs planned to buy, with populated price & amount
	QString teamName;
	double total = 0;
	QVector<W_NewSouvenir*> souvenirWidgets;
	W_SelectSouvenir* selectSouvenirWidget;
	bool hasSelectSouvenir = false;

	void updateTotal();
	void triggerAddSouvenir(Souvenir souvenir);

	void populateSouvenirs();
	void addSouvenirToList(Souvenir souvenir);
	void removeSouvenirFromList(QString souvenirName); // Called from signal
	void onUpdate(Souvenir souvenir); // Called from signal
};
