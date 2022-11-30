#include "DisplayDistances.h"
#include "Database.h"

Database distanceDB;

DisplayDistances::DisplayDistances(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	initializeList();
	QObject::connect(ui.teamSelect, &QComboBox::currentTextChanged, this, &DisplayDistances::displayAllDistances);
}

DisplayDistances::~DisplayDistances()
{}

void DisplayDistances::open()
{
	initializeList();
	displayAllDistances();
}

void DisplayDistances::initializeList()
{

	QVector<Team> teams = distanceDB.getTeams();
	ui.teamSelect->clear();
	for (int i = 0; i < teams.size(); i++)
	{
		QString teamName = teams[i].getTeamName();
		ui.teamSelect->addItem(teamName);
	}
}

void DisplayDistances::clearLayout()
{
	for (int i = 0; i < allWidgets.size(); i++)
	{
		ui.souvenirLayout->layout()->removeWidget(allWidgets.at(i));
		delete allWidgets[i];
	}
	allWidgets.clear();
}


void DisplayDistances::displayAllDistances()
{
	clearLayout();
	QString teamName = ui.teamSelect->currentText();
	QVector<Team> allTeams = distanceDB.getTeams();
	qDebug() << "SIZE: " << allTeams.size();
	for (int i = 0; i < allTeams.size(); i++)
	{

		QVector<Distance> allDistances = allTeams[i].getStadium().getAllEdges();

		if (allTeams[i].getTeamName() == teamName)
		{
			for (int j = 0; j < allDistances.size(); j++)
			{
				W_DistanceList* newDistance = new W_DistanceList(this);
				newDistance->setup(allDistances[j].getStartingStadium(), allDistances[j].getEndingStadium(), allDistances[j].getDistance());
				ui.verticalLayout_2->addWidget(newDistance);
				allWidgets.push_back(newDistance);

			}
		}
	}
}