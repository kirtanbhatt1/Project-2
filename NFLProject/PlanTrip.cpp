#include "PlanTrip.h"

Database database;

PlanTrip::PlanTrip(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.page_switcher->setCurrentIndex(1);
	ui.C_PlanTeams->setAlignment(Qt::AlignTop);
	ui.C_PlanCustom->setAlignment(Qt::AlignTop);
	ui.SA_TeamList->setAlignment(Qt::AlignTop);

	// Get teams data to use for methods
	stadiumsData = database.getAllStadiums();
	distancesData = database.distances;

	ui.ScrollContents_TeamsList->setAlignment(Qt::AlignTop);
	ui.S_NumOfTeams->setMinimum(0);
	if (stadiumsData.length() > 0) 
	{
		// Setup UI
		ui.S_NumOfTeams->setMaximum((stadiumsData.length() - 1));
		ui.S_NumOfTeams->setValue((stadiumsData.length() - 1));
		ui.L_NumOfTeams->setText(QString::number(stadiumsData.length() - 1));
		numberOfTeams = stadiumsData.length() - 1;

		//change get team name to get stadium name
		//startingTeam = stadiumsData[0].getTeamName();
		startingTeam = stadiumsData[0].getStadiumName();

		for (int i = 0; i < stadiumsData.length(); i++) 
		{
			//ui.CB_SelectTeam->addItem(stadiumsData[i].getTeamName());
			//ui.CB_CustomStartingTeam->addItem(stadiumsData[i].getTeamName());
			
			ui.CB_SelectTeam->addItem(stadiumsData[i].getStadiumName());
			ui.CB_CustomStartingTeam->addItem(stadiumsData[i].getStadiumName());
		}
		if (stadiumsData.length() > 0) ui.CB_SelectTeam->setCurrentIndex(0);
		if (stadiumsData.length() > 0) ui.CB_CustomStartingTeam->setCurrentIndex(0);
	}

	// Connections
	QObject::connect(ui.S_NumOfTeams, &QSlider::valueChanged, this, &PlanTrip::selectNumberOfTeams);
	QObject::connect(ui.CB_SelectTeam, &QComboBox::currentIndexChanged, this, &PlanTrip::teamSelected);
	QObject::connect(ui.CB_CustomStartingTeam, &QComboBox::currentIndexChanged, this, &PlanTrip::teamSelected);
	QObject::connect(ui.B_CustomNext, &QPushButton::clicked, this, &PlanTrip::switch2nd);
	QObject::connect(ui.B_ShortestNext, &QPushButton::clicked, this, &PlanTrip::switch2nd);
	QObject::connect(ui.B_Back, &QPushButton::clicked, this, &PlanTrip::triggerBack);
}

PlanTrip::~PlanTrip()
{}

void PlanTrip::open(TripMode mode)
{
	tripMode = mode;
	switch (mode) 
	{
	case shortest:
		ui.teamsInput_switcher->setCurrentIndex(0);
		beginPlan();
		break;
	case custom:
		ui.teamsInput_switcher->setCurrentIndex(1);
		beginPlan();
		break;
	}
}

// Graph PlanTrip::getGraphCities()
// {
// 	return cities;
// }

// void PlanTrip::initializeEdges(QVector<Team> allCities)
// {
// 	for (int i = 0; i < allCities.size(); i++)
// 	{
// 		getGraphCities().insertVertex(allCities[i].getStadiumName());

// 		for (int j = 0; allCities[i].getAllEdges().size(); j++)
// 		{
// 			getGraphCities().insertEdge(allCities[j].getAllEdges()[j].getStartingStadium(), allCities[j].getAllEdges()[j].getEndingStadium(), allCities[j].getAllEdges()[j].getDistance());
// 		}
// 	}

// }

// void PlanTrip::depthFirstSearch()
// {
// 	getGraphCities().DFS(getGraphCities().getVertex("U.S. Bank Stadium"));

// }

void PlanTrip::beginPlan()
{
//Database database;
//	database.initializeMap();

	totalDistance = 0;
	plannedTeams.clear();

	if (tripMode == shortest)
	{
		// Clear data:
		for (int i = 0; i < w_teamsList.length(); i++)
		{
			ui.ScrollContents_TeamsList->layout()->removeWidget(w_teamsList.at(i));
			delete w_teamsList[i];
		}
		w_teamsList.clear();

		// Create top of box
		qDebug() << "Selected team: " << startingTeam;
		W_TeamDistanceList* w_team = new W_TeamDistanceList(this);
		w_team->setup(startingTeam);
		w_teamsList.push_back(w_team);
		ui.ScrollContents_TeamsList->layout()->addWidget(w_team);
		plannedTeams.push_back(startingTeam);
	
	   // May have to repopulate the distances data
		distancesData = database.distances;
		
		// Begin recursive search:
		calculateShortestPlan(startingTeam, numberOfTeams);
		ui.L_TotalDistanceShort->setText(QString::number(totalDistance) + "km");
	}

	else if (tripMode == custom) 
	{
		// Clear data:
		for (int i = 0; i < w_teamsList.length(); i++) 
		{
			ui.C_PlanCustom->layout()->removeWidget(w_teamsList.at(i));
			delete w_teamsList[i];
		}
		w_teamsList.clear();
		for (int i = 0; i < w_TeamToggles.length(); i++) 
		{
			ui.C_PlanTeams->layout()->removeWidget(w_TeamToggles.at(i));
			delete w_TeamToggles[i];
		}
		w_TeamToggles.clear();

		// Populate TeamToggles box (All teams except for the starting team)
		for (int i = 0; i < stadiumsData.length(); i++) 
		{
			//changed get team name to get stadium name
			//if (stadiumsData[i].getTeamName() == startingTeam) continue;
			if (stadiumsData[i].getStadiumName() == startingTeam) continue;
			
			TeamToggle* w_toggleTeam = new TeamToggle(this);
			//w_toggleTeam->setup(selectedTeams.contains(stadiumsData[i].getTeamName()), stadiumsData[i].getTeamName());
			w_toggleTeam->setup(selectedTeams.contains(stadiumsData[i].getStadiumName()), stadiumsData[i].getStadiumName() );
			
			QObject::connect(w_toggleTeam, &TeamToggle::stateChanged, this, &PlanTrip::teamToggled);
			w_TeamToggles.push_back(w_toggleTeam);
			ui.C_PlanTeams->layout()->addWidget(w_toggleTeam);
		}

		// Add starting team
		W_TeamDistanceList* w_team = new W_TeamDistanceList(this);
		w_team->setup(startingTeam);
		w_teamsList.push_back(w_team);
		ui.C_PlanCustom->layout()->addWidget(w_team);
		plannedTeams.push_back(startingTeam);

		// Repopulate the data for recursive function
		distancesData = database.distances;
		//for (int i = 0; i < distancesData.size(); i++)
		//{
		//	qInfo() << "RECURSIVE FUNCTION DISTANCES DATA INDEX " << i << distancesData[i].getStartingStadium(); 
		//}

		// Adds the selected team so its in the list of selected team
		selectedTeams.push_back(startingTeam);
		selectedTeams.removeDuplicates();

		// Remove distance data that is not of the list of selected teams.
		for (int i = 0; i < distancesData.length(); i++) 
		{
			//needs fixing
			if (!selectedTeams.contains(distancesData[i].getStartingStadium()) || !selectedTeams.contains(distancesData[i].getEndingStadium())) {
				distancesData.removeAt(i);
				i--;
			}
		}
		
		for (Distance distance : distancesData)
		{
			qInfo() << distance.getDistance();
		}

		// Recursively populate plan teams list (should only show teams that are toggled on)
		calculateCustomPlan(startingTeam, distancesData);
		ui.L_TotalDistanceCustom->setText(QString::number(totalDistance) + "km");
	}
}

void PlanTrip::calculateShortestPlan(QString startingTeam, int teamsLeft)
{
	// Calculates the shortest distance from the starting team recursively and adds it to the display.
	if (teamsLeft <= 0) return;
	double shortestDistance = 999999;
	QString nearestTeam = "";

	for (int i = 0; i < distancesData.length(); i++) 
	{
		// Look through the distances to find distances related to the team and 
		
		//needs fixing
		if (distancesData[i].getStartingStadium() == startingTeam || distancesData[i].getEndingStadium() == startingTeam) 
		{
			if (distancesData[i].getDistance() < shortestDistance) 
			{
				shortestDistance = distancesData[i].getDistance();

				// Choose which team
				if (distancesData[i].getStartingStadium() != startingTeam)
				{
					nearestTeam = distancesData[i].getStartingStadium();
					qDebug() << "IF Statement on line 221 is hitting.";
				}
				else 
				{
					nearestTeam = distancesData[i].getEndingStadium();
					qDebug() << "ELSE Statement on line 221 is hitting.";
				}
			}
			// Remove distanceData so it isn't searched for again
			distancesData.removeAt(i);
			i--;
		}
	}
	//
	if (nearestTeam.isEmpty()) 
	{
		qDebug() << "Could not find shortest team!";
		return;
	}

	addToTeamList(nearestTeam, shortestDistance);
	calculateShortestPlan(nearestTeam, --teamsLeft);
}



void PlanTrip::addToTeamList(QString team, double distance)
{
	//qDebug() << "Adding team: " << team << " with distance " << distance;
	W_TeamDistanceList* teamList = new W_TeamDistanceList(this);
	teamList->setup(team, distance);
	ui.ScrollContents_TeamsList->layout()->addWidget(teamList);
	w_teamsList.push_back(teamList);
	totalDistance += distance;
	plannedTeams.push_back(team);
}

void PlanTrip::selectNumberOfTeams(int value)
{
	//qDebug() << "SelectNumberOfCities value changed " << value;
	ui.L_NumOfTeams->setText(QString::number(value));
	numberOfTeams = value;

	beginPlan();
}

void PlanTrip::teamSelected(int index)
{
	// Called when the combo box value changes
	// Remove the previous selected team
	if (tripMode == custom) 
	{
		for (int i = 0; i < selectedTeams.length(); i++) 
		{
			if (selectedTeams.at(i) == startingTeam) 
			{
				selectedTeams.removeAt(i);
				break;
			}
		}
	}

	startingTeam = stadiumsData[index].getStadiumName();
	beginPlan();
}

void PlanTrip::addToCustomTeamList(QString team, double distance)
{
	W_TeamDistanceList* teamList = new W_TeamDistanceList(this);
	teamList->setup(team, distance);
	ui.C_PlanCustom->layout()->addWidget(teamList);
	w_teamsList.push_back(teamList);
	totalDistance += distance;
	plannedTeams.push_back(team);
}

void PlanTrip::calculateCustomPlan(QString startingTeam, QVector<Distance>& distances)
{
//	Database database;
	//database.initializeMap();

	for (int i = 0; i < distancesData.size(); i++)
	{
		qInfo() << distancesData[i].getDistance();
	}

	//qDebug() << "Calculating for " << startingTeam << " with " << distances.length() << " teams left.";
	if (distances.length() == 0) return;
	double shortestDistance = 999999;
	QString nearestTeam = "";

	for (int i = 0; i < distances.length(); i++) 
	{
		// Look through the distances to find distances related to the team.
		if (distances[i].getStartingStadium() == startingTeam || distances[i].getEndingStadium() == startingTeam) 
		{
			if (distances[i].getDistance() < shortestDistance) 
			{
				qInfo() << distances[i].getDistance();
				shortestDistance = distances[i].getDistance();

				// Choose which team
				if (distances[i].getStartingStadium() != startingTeam)
				{
					nearestTeam = distances[i].getStartingStadium();
				}
				else
				{
					nearestTeam = distances[i].getEndingStadium();
				}
			}
			// Remove distance data so it isn't searched for again
			 distances.removeAt(i);
			i--;
		}
	}
	if (nearestTeam.isEmpty()) 
	{
		qDebug() << "Could not find shortest team!";
		return;
	}
	addToCustomTeamList(nearestTeam, shortestDistance);
	calculateCustomPlan(nearestTeam, distances);
}

// Adds or removes to the list of selected teams for the custom menu
void PlanTrip::teamToggled(bool value, QString team)
{
	if (value) 
	{
		selectedTeams.push_back(team);
		selectedTeams.removeDuplicates();
	}
	else 
	{
		for (int i = 0; i < selectedTeams.length(); i++) 
		{
			if (selectedTeams.at(i) == team) 
			{
				selectedTeams.removeAt(i);
				break;
			}
		}
	}
	// Refresh
	beginPlan();
}


// When menu is switched.
void PlanTrip::switch2nd()
{
	// Check if theres atleast 1 other team


	QVector<Team> teams = database.getTeams();

	ui.page_switcher->setCurrentIndex(0);
	// Fill scroll box with teams & their foods
	for (QString teamName : plannedTeams) 
	{
		W_AddTeamSouvenirs* teamWidget = new W_AddTeamSouvenirs(this);

		Team teamData = database.getTeam(teamName);
		teamWidget->setup(teamData);
		addedTeams.push_back(teamWidget);
		ui.SA_TeamList->layout()->addWidget(teamWidget);
		QObject::connect(teamWidget, &W_AddTeamSouvenirs::priceUpdated, this, &PlanTrip::totalPriceUpdated);
	}
}


void PlanTrip::totalPriceUpdated(double price)
{
	// Loop through teams to get their price and number of purchases.
	double total = 0;
	int count = 0;
	for (W_AddTeamSouvenirs* addedTeam : addedTeams) 
	{
		total += addedTeam->getTotal();
		count += addedTeam->numOfPurchases();
	}
	ui.L_TotalCost->setText("$" + QString::number(total, 'f', 2));
	ui.L_NumberPurchasedSouvenirs->setText(QString::number(count));
}


void PlanTrip::triggerBack()
{
	ui.page_switcher->setCurrentIndex(1);
	for (int i = 0; i < addedTeams.length(); i++) 
	{
		ui.SA_TeamList->layout()->removeWidget(addedTeams[i]);
		delete addedTeams[i];
	}
	addedTeams.clear();
	totalPriceUpdated(0);
}
