#pragma once

#include <QMainWindow>
#include "ui_DisplaySorted.h"
#include "W_SortedList.h"
#include <QWidget>
#include "Database.h"
#include "Team.h"
#include <QCheckbox>

class DisplaySorted : public QMainWindow
{
	Q_OBJECT

public:
	DisplaySorted(QWidget *parent = nullptr);
	~DisplaySorted();

	void displayAllSortedTeams(QVector<Team> sortedTeams);

	void sortAlphabetically();

	void sortAmericanConferenceTeams();

	void sortNationalFootballTeams();

	void sortNFCNorthTeams();

	void sortOpenRoofType();

	void sortByDate();

	void sortByCapacity();

	void sortByConference();

	void clearLayout();

private:
	Ui::DisplaySortedClass ui;
	QVector<Team> sortedTeams;
	QVector<W_SortedList*> allWidgets;
};
