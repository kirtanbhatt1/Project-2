#include "DisplaySorted.h"
#include "ui_DisplaySorted.h"
#include "Database.h"
Database sortedDb;

DisplaySorted::DisplaySorted(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	//connect checkboxes to sort functions
	QObject::connect(ui.T_Alphabetical, &QPushButton::clicked, this, &DisplaySorted::sortAlphabetically);
	QObject::connect(ui.T_AFC, &QPushButton::clicked, this, &DisplaySorted::sortAmericanConferenceTeams);
	QObject::connect(ui.T_NFC, &QPushButton::clicked, this, &DisplaySorted::sortNationalFootballTeams);
	QObject::connect(ui.T_NFCNorth, &QPushButton::clicked, this, &DisplaySorted::sortNFCNorthTeams);
	QObject::connect(ui.T_Open, &QPushButton::clicked, this, &DisplaySorted::sortOpenRoofType);
	QObject::connect(ui.T_Stadium, &QPushButton::clicked, this, &DisplaySorted::sortStadiumName);
	QObject::connect(ui.T_Date, &QPushButton::clicked, this, &DisplaySorted::sortByDate);
	QObject::connect(ui.T_Capacity, &QPushButton::clicked, this, &DisplaySorted::sortByCapacity);
	QObject::connect(ui.T_Conference, &QPushButton::clicked, this, &DisplaySorted::sortByConference);

		
}

DisplaySorted::~DisplaySorted()
{}


void DisplaySorted::displayAllSortedTeams(QVector<Team> sortedTeams )
{
	int totalCount = 0;
		
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
	clearLayout();
	QVector<Team> allTeams = sortedDb.getTeams();
	displayAllSortedTeams(allTeams);

}


void DisplaySorted::sortAmericanConferenceTeams()
{
	clearLayout();
	QVector<Team> allTeams = sortedDb.getTeams();
	QVector<Team> newTeams;

	for (int i = 0; i < allTeams.size(); i++)
	{
		if (allTeams[i].getConference() == "American Football Conference")
		{
			newTeams.push_back(allTeams[i]);
		}
	}

	displayAllSortedTeams(newTeams);

}

void DisplaySorted::sortNationalFootballTeams()
{
	clearLayout();
	QVector<Team> allTeams = sortedDb.getTeams();
	QVector<Team> newTeams;

	for (int i = 0; i < allTeams.size(); i++)
	{
		if (allTeams[i].getConference() == "National Football Conference")
		{
			newTeams.push_back(allTeams[i]);
		}
	}

	displayAllSortedTeams(newTeams);
}

void DisplaySorted::sortNFCNorthTeams()
{
	clearLayout();
	QVector<Team> allTeams = sortedDb.getTeams();
	QVector<Team> newTeams;

	for (int i = 0; i < allTeams.size(); i++)
	{
		if (allTeams[i].getDivision() == "NFC North")
		{
			newTeams.push_back(allTeams[i]);
		}
	}

	displayAllSortedTeams(newTeams);

}

void DisplaySorted::sortOpenRoofType()
{
	clearLayout();
	QVector<Team> allTeams = sortedDb.getTeams();
	QVector<Team> newTeams;
	int totalCount = 0;
	
	for (int i = 0; i < allTeams.size(); i++)
	{
		if (allTeams[i].getStadium().getRoofType() == "Open")
		{
			newTeams.push_back(allTeams[i]);
			totalCount++;
		}		
	}
	totalCount = removeDuplicateStadiums(newTeams, totalCount);

	std::sort(newTeams.begin(), newTeams.end(), Team::compareStadium);
	displayAllSortedTeams(newTeams);
	
	//adding total number of open stadiums widget at bottom of display menu
	W_TotalCount* count = new W_TotalCount(this);
	count->setup(totalCount);
	ui.vertical_details_layout->addWidget(count);
	allCountWidgets.push_back(count);
}
void DisplaySorted::sortStadiumName()
{
	clearLayout();
	QVector<Team> allTeams = sortedDb.getTeams();
	std::sort(allTeams.begin(), allTeams.end(), Team::compareStadium);
	displayAllSortedTeams(allTeams);



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

	long totalCapacity = sortedDb.getTotalCapacity(allTeams);
	
	for (int i = 0; i < allTeams.size(); i++) {
		for (int j = i; j < (allTeams.size()); j++) {

			if (allTeams[i].getStadium().getCapacity() > allTeams[j].getStadium().getCapacity()) {

				std::swap(allTeams[i], allTeams[j]);
			}
		}
	}

	

	displayAllSortedTeams(allTeams);

	totalCapacity = removeDuplicateCapacity(allTeams, totalCapacity);

	//adding total number of open stadiums widget at bottom of display menu
	W_TotalCount* count = new W_TotalCount(this);

	count->setup(totalCapacity);

	count->setLabelText("TOTAL CAPACITY: ");

	ui.vertical_details_layout->addWidget(count);

	allCountWidgets.push_back(count);


}

void DisplaySorted::sortByConference()
{
	clearLayout();
	QVector<Team> allTeams = sortedDb.getTeams();
	std::sort(allTeams.begin(), allTeams.end(), Team::compareConference);
	displayAllSortedTeams(allTeams);

}
	

void DisplaySorted::clearLayout()
{
	for (int i = 0; i < allWidgets.size(); i++)
	{
		ui.vertical_details_layout->layout()->removeWidget(allWidgets.at(i));
		delete allWidgets[i];
	}
	allWidgets.clear();

	clearCount();
}

void DisplaySorted::clearCount()
{
	for (int i = 0; i < allCountWidgets.size(); i++)
	{
		ui.vertical_details_layout->layout()->removeWidget(allCountWidgets.at(i));
		delete allCountWidgets[i];
	}
	allCountWidgets.clear();
}

int DisplaySorted::removeDuplicateStadiums(QVector<Team>& vec, int totalCount) {
	

	for (int i = 0; i < vec.size(); ++i) {
		for (int j = i + 1; j < vec.size(); ++j) {
			if (vec[i].getStadium().getStadiumName() == vec[j].getStadium().getStadiumName())
				totalCount = totalCount - 1;
		}
	}
	return totalCount;
}

long DisplaySorted::removeDuplicateCapacity(QVector<Team>& vec, long totalCapacity) {


	for (int i = 0; i < vec.size(); ++i) {
		for (int j = i + 1; j < vec.size(); ++j) {
			if (vec[i].getStadium().getStadiumName() == vec[j].getStadium().getStadiumName())
				totalCapacity -= vec[j].getStadium().getCapacity().toLong();
		}
	}
	return totalCapacity;
}