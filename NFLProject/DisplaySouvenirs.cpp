#include "DisplaySouvenirs.h"
#include "Database.h"

Database souvenirDB;

DisplaySouvenirs::DisplaySouvenirs(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	initializeList();
	QObject::connect(ui.teamSelect, &QComboBox::currentTextChanged, this, &DisplaySouvenirs::displayAllSouvenirs);
}

DisplaySouvenirs::~DisplaySouvenirs()
{}

void DisplaySouvenirs::open()
{
	initializeList();
	displayAllSouvenirs();
}

void DisplaySouvenirs::initializeList()
{

	QVector<Team> teams = souvenirDB.getTeams();

	for (int i = 0; i < teams.size(); i++)
	{
		QString teamName = teams[i].getTeamName();
		ui.teamSelect->addItem(teamName);
	}
}

void DisplaySouvenirs::clearLayout()
{
	for (int i = 0; i < allWidgets.size(); i++)
	{
		ui.souvenirLayout->layout()->removeWidget(allWidgets.at(i));
		delete allWidgets[i];
	}
	allWidgets.clear();
}


void DisplaySouvenirs::displayAllSouvenirs()
{
	clearLayout();
	QString teamName = ui.teamSelect->currentText();
	QVector<Team> allTeams = souvenirDB.getTeams();
	qDebug() << "SIZE: " << allTeams.size();
	for (int i = 0; i < allTeams.size(); i++)
	{	

		QVector<Souvenir> allSouvenirs = allTeams[i].getStadium().getSouvenirs(); 

		if (allTeams[i].getTeamName() == teamName)
		 {
			for (int j = 0; j < allSouvenirs.size(); j++)
			{
				W_SouvenirList* souvenirItem = new W_SouvenirList(this);
				souvenirItem->setup(allSouvenirs[j].getName(), allSouvenirs[j].getPrice());
				ui.verticalLayout_2->addWidget(souvenirItem);
				allWidgets.push_back(souvenirItem);
				
			}
		}
	}
}