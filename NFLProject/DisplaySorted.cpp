#include "DisplaySorted.h"
#include "ui_DisplaySorted.h"
#include "Database.h"

DisplaySorted::DisplaySorted(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	initializeTeamsList();
	displayAllTeams();

	// Connect checkboxes to sort functions
	//connect(ui.T_Alphabetical, &QAction::isChecked, this, &DisplaySorted::sortAlphabetically);
	//connect(ui.T_AFC, &QAction::toggled, this, &DisplaySorted::sortAmericanConferenceTeams);
	//connect(ui.T_NFC, &QAction::toggled, this, &DisplaySorted::sortNationalFootballTeams);
	//connect(ui.T_NFCNorth, &QAction::toggled, this, &DisplaySorted::sortNFCNorthTeams);
	//connect(ui.T_Open, &QAction::toggled, this, &DisplaySorted::sortOpenRoofType);
	//connect(ui.T_Date, &QAction::toggled, this, &DisplaySorted::sortByDate);
	//connect(ui.T_Capacity, &QAction::toggled, this, &DisplaySorted::sortByCapacity);
	//connect(ui.T_Conference, &QAction::toggled, this, &DisplaySorted::sortByConference);
		

}

DisplaySorted::~DisplaySorted()
{}


void DisplaySorted::displayAllTeams(/*QVector<Team> sortedTeams*/ )
{
	QVector<Team> teams = sortedTeams;
		
	for (int i = 0; i < teams.size(); i++)
	{
		W_SortedList* team = new W_SortedList(this);
		team->setup(teams[i].getTeamName(), teams[i].getStadium().getStadiumName(),
			teams[i].getStadium().getCapacity(), teams[i].getStadium().getLocation(),
			teams[i].getStadium().getRoofType(), teams[i].getStadium().getSurface(),
			teams[i].getConference(), teams[i].getStadium().getOpenedYear(),
			teams[i].getDivision());
		ui.vertical_details_layout->addWidget(team);
	}
}


void DisplaySorted::initializeTeamsList()
{
	Database database;
	sortedTeams = database.getTeams();
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


}

void DisplaySorted::sortByCapacity()
{

}

void DisplaySorted::sortByConference()
{

}
	

