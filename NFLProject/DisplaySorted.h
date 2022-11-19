#pragma once

#include <QMainWindow>
#include "ui_DisplaySorted.h"
#include "W_SortedList.h"
#include "W_TotalCount.h"
#include <QWidget>
#include "Database.h"
#include "Team.h"
#include <algorithm>
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

	void sortStadiumName();

	void sortByCapacity();

	void sortByConference();

	void clearLayout();

	void clearCount();
	
	int removeDuplicateStadiums( QVector<Team>& vec, int totalCount);
	long removeDuplicateCapacity(QVector<Team>& vec, long totalCapacity);
	
private:
	Ui::DisplaySortedClass ui;
	QVector<Team> sortedTeams;
	QVector<W_SortedList*> allWidgets;
	QVector<W_TotalCount*> allCountWidgets;
};
