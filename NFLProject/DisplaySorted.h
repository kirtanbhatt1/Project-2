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

	void displayAllTeams();
	// This function looks into the private vector after sorting and displays
	// the values after using initializeTeamsList

	void initializeTeamsList();
	// This function adds the teams db into a vector
	
	void sortAlphabetically();

	void sortAmericanConferenceTeams();

	void sortNationalFootballTeams();

	void sortNFCNorthTeams();

	void sortOpenRoofType();

	void sortByDate();

	void sortByCapacity();

	void sortByConference();

private:
	Ui::DisplaySortedClass ui;
	QVector<Team> sortedTeams;

};
