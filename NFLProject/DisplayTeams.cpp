#include "DisplayTeams.h"
#include "Database.h"
#include "ui_DisplayTeams.h"

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
	QVector<Team> teams = Database::getTeams();
	for (int i = 0; i < teams.size(); i++)
	{
		ui.teamSelect->addItem(teams[i].teamName);
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
	QVector<Team> allTeams = Database::getTeams();
	for (int i = 0; i < allTeams.size(); i++)
	{
		if (allTeams[i].teamName == teamName)
		{
			W_TeamsList* team = new W_TeamsList(this);
			team->setup(teamName, allTeams[i].stadium, allTeams[i].capacity, allTeams[i].location, allTeams[i].roofType,
				allTeams[i].surface, allTeams[i].conference, allTeams[i].opened, allTeams[i].division);
			ui.vertical_food_layout->addWidget(team);
			allWidgets.push_back(team);
		}
	}
}
