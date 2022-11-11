#include "DisplayTeams.h"
#include "Database.h"
#include "ui_DisplayTeams.h"

Database nfl_db;

DisplayTeams::DisplayTeams(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	QObject::connect(ui.teamSelect, &QComboBox::currentTextChanged, this, &DisplayTeams::displayAllTeams);
}

DisplayTeams::~DisplayTeams()
{}
void DisplayTeams::initializeList()
{
	QVector<Team> teams = nfl_db.getTeams();
	for (int i = 0; i < teams.size(); i++)
	{
		QString name = teams[i].getTeamName();
		ui.teamSelect->addItem(name);
	}
}
void DisplayTeams::open()
{
	initializeList();
	displayAllTeams();
}
void DisplayTeams::clearLayout()
{
	for (int i = 0; i < allWidgets.size(); i++)
	{
		ui.vertical_food_layout->layout()->removeWidget(allWidgets.at(i));
		delete allWidgets[i];
	}
	allWidgets.clear();
}
void DisplayTeams::displayAllTeams()
{
	clearLayout();
	QString teamName = ui.teamSelect->currentText();
	QVector<Team> allTeams = nfl_db.getTeams();
	for (int i = 0; i < allTeams.size(); i++)
	{
		if (allTeams[i].getTeamName() == teamName)
		{
			W_TeamsList* team = new W_TeamsList(this);
			team->setup(teamName, allTeams[i].getStadium().getStadiumName(), allTeams[i].getStadium().getCapacity(), allTeams[i].getStadium().getLocation(),
				allTeams[i].getStadium().getRoofType(), allTeams[i].getStadium().getSurface(), allTeams[i].getConference(), allTeams[i].getStadium().getOpenedYear(),
				allTeams[i].getDivision());
			ui.vertical_food_layout->addWidget(team);
			allWidgets.push_back(team);
		}
	}
}