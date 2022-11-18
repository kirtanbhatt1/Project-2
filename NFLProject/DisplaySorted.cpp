#include "DisplaySorted.h"
#include "ui_DisplaySorted.h"
#include "Database.h"

Database sortedDb;

DisplaySorted::DisplaySorted(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	//connect checkboxes to sort functions
	QObject::connect(ui.T_Alphabetical, &QCheckBox::toggled, this, &DisplaySorted::sortAlphabetically);
	QObject::connect(ui.T_AFC, &QCheckBox::toggled, this, &DisplaySorted::sortAmericanConferenceTeams);
	QObject::connect(ui.T_NFC, &QCheckBox::toggled, this, &DisplaySorted::sortNationalFootballTeams);
	QObject::connect(ui.T_NFCNorth, &QCheckBox::toggled, this, &DisplaySorted::sortNFCNorthTeams);
	QObject::connect(ui.T_Open, &QCheckBox::toggled, this, &DisplaySorted::sortOpenRoofType);
	QObject::connect(ui.T_Date, &QCheckBox::toggled, this, &DisplaySorted::sortByDate);
	QObject::connect(ui.T_Capacity, &QCheckBox::toggled, this, &DisplaySorted::sortByCapacity);
	QObject::connect(ui.T_Conference, &QCheckBox::toggled, this, &DisplaySorted::sortByConference);

		

}

DisplaySorted::~DisplaySorted()
{}


void DisplaySorted::displayAllSortedTeams(QVector<Team> sortedTeams )
{
		
	for (int i = 0; i < sortedTeams.size(); i++)
	{
		W_SortedList* team = new W_SortedList(this);
		team->setup(sortedTeams[i].getTeamName(), sortedTeams[i].getStadium().getStadiumName(),
			sortedTeams[i].getStadium().getCapacity(), sortedTeams[i].getStadium().getLocation(),
			sortedTeams[i].getStadium().getRoofType(), sortedTeams[i].getStadium().getSurface(),
			sortedTeams[i].getConference(), sortedTeams[i].getStadium().getOpenedYear(),
			sortedTeams[i].getDivision());
		ui.vertical_details_layout->addWidget(team);
		allWidgets.push_back(team);
	}
}

void DisplaySorted::sortAlphabetically()
{
	

}


void DisplaySorted::sortAmericanConferenceTeams()
{


}

void DisplaySorted::sortNationalFootballTeams()
{

}

void DisplaySorted::sortNFCNorthTeams()
{


}

void DisplaySorted::sortOpenRoofType()
{


}

void DisplaySorted::sortByDate()
{
	clearLayout();

	QVector<Team> allTeams = sortedDb.getTeams();
	for (int i = 0; i < allTeams.size(); i++) {
		for (int j = i; j < (allTeams.size()); j++) {
			if (allTeams[i].getStadium().getOpenedYear() > allTeams[j].getStadium().getOpenedYear()) {
				std::swap(allTeams[i], allTeams[j]);
			}
		}
	}

	displayAllSortedTeams(allTeams);

}

void DisplaySorted::sortByCapacity()
{
	clearLayout();

	QVector<Team> allTeams = sortedDb.getTeams();
	for (int i = 0; i < allTeams.size(); i++) {
		for (int j = i; j < (allTeams.size()); j++) {
			if (allTeams[i].getStadium().getCapacity() > allTeams[j].getStadium().getCapacity()) {
				std::swap(allTeams[i], allTeams[j]);
			}
		}
	}

	displayAllSortedTeams(allTeams);
}

void DisplaySorted::sortByConference()
{

}
	

void DisplaySorted::clearLayout()
{
	for (int i = 0; i < allWidgets.size(); i++)
	{
		ui.vertical_details_layout->layout()->removeWidget(allWidgets.at(i));
		delete allWidgets[i];
	}
	allWidgets.clear();
}
