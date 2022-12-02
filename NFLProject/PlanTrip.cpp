#include "PlanTrip.h"

PlanTrip::PlanTrip(QWidget *parent)
	: QWidget(parent)
{
	Database database;

	ui.setupUi(this);
	ui.page_switcher->setCurrentIndex(0);
	ui.C_PlanTeams->setAlignment(Qt::AlignTop);
	ui.C_PlanCustom->setAlignment(Qt::AlignTop);
	ui.SA_TeamList->setAlignment(Qt::AlignTop);

	// Get cities data to use for methods
	teamsData = database.getTeams();
	distancesData = Database::getAllDistances();

	ui.ScrollContents_TeamsList->setAlignment(Qt::AlignTop);
	ui.S_NumOfTeams->setMinimum(0);
	if (teamsData.length() > 0) 
	{
		// Setup UI
		ui.S_NumOfTeams->setMaximum(teamsData.length() - 1);
		ui.S_NumOfTeams->setValue(teamsData.length() - 1);
		ui.L_NumOfTeams->setText(QString::number(teamsData.length() - 1));
		numberOfTeams = teamsData.length() - 1;
		startingTeam = teamsData[0].getTeamName();

		for (int i = 0; i < teamsData.length(); i++) {
			ui.CB_SelectTeam->addItem(teamsData[i].getTeamName());
			ui.CB_CustomStartingTeam->addItem(teamsData[i].getTeamName());
		}
		if (teamsData.length() > 0) ui.CB_SelectTeam->setCurrentIndex(0);
		if (teamsData.length() > 0) ui.CB_CustomStartingTeam->setCurrentIndex(0);
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
	switch (mode) {
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

Graph PlanTrip::getGraphCities()
{
	return cities;
}

void PlanTrip::initializeEdges(QVector<Team> allCities)
{
	for (int i = 0; i < allCities.size(); i++)
	{
		getGraphCities().insertVertex(allCities[i].getStadium().getStadiumName());

		for (int j = 0; allCities[i].getStadium().getAllEdges().size(); j++)
		{
			getGraphCities().insertEdge(allCities[j].getStadium().getAllEdges()[j].getStartingStadium(), allCities[j].getStadium().getAllEdges()[j].getEndingStadium(), allCities[j].getStadium().getAllEdges()[j].getDistance());
		}
	}

}

void PlanTrip::depthFirstSearch()
{
	getGraphCities().DFS(getGraphCities().getVertex("U.S. Bank Stadium"));

}

void PlanTrip::beginPlan()
{
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
		distancesData = Database::getAllDistances();

		// Begin recursive search:
		calculateShortestPlan(startingTeam, numberOfTeams);
		ui.L_TotalDistanceShort->setText(QString::number(totalDistance) + "km");
	}

	else if (tripMode == custom) 
	{
		// Clear data:
		for (int i = 0; i < w_teamsList.length(); i++) {
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

		// Populate CityToggles box (All cities except for the starting city)
		for (int i = 0; i < teamsData.length(); i++) 
		{
			if (teamsData[i].getTeamName() == startingTeam) continue;
			TeamToggle* w_toggleTeam = new TeamToggle(this);
			w_toggleTeam->setup(selectedTeams.contains(teamsData[i].getTeamName()), teamsData[i].getTeamName());
			QObject::connect(w_toggleTeam, &TeamToggle::stateChanged, this, &PlanTrip::teamToggled);
			w_TeamToggles.push_back(w_toggleTeam);
			ui.C_PlanTeams->layout()->addWidget(w_toggleTeam);
		}

		// Add starting city
		W_TeamDistanceList* w_team = new W_TeamDistanceList(this);
		w_team->setup(startingTeam);
		w_teamsList.push_back(w_team);
		ui.C_PlanCustom->layout()->addWidget(w_team);
		plannedTeams.push_back(startingTeam);

		//// Repopulate the data for recursive function
		distancesData = Database::getAllDistances();

		// Adds the selected city so its in the list of selected cities
		selectedTeams.push_back(startingTeam);
		selectedTeams.removeDuplicates();

		// Remove distance data that is not of the list of selected cities.
		for (int i = 0; i < distancesData.length(); i++) 
		{
			if (!selectedTeams.contains(distancesData[i].getStartingStadium()) || !selectedTeams.contains(distancesData[i].getEndingStadium())) {
				distancesData.removeAt(i);
				i--;
			}
		}

		// Recursively populate plan cities list (should only show cities that are toggled on)
		calculateCustomPlan(startingTeam, distancesData);
		ui.L_TotalDistanceCustom->setText(QString::number(totalDistance) + "km");
	}
}

void PlanTrip::calculateShortestPlan(QString startingTeam, int teamsLeft)
{
	//qDebug() << "Calculating for " << startingTeam << " with " << teamsLeft << " teams left.";
	// Calculates the shortest distance from the starting city recursively and adds it to the display.
	if (teamsLeft <= 0) return;
	double shortestDistance = 999999;
	QString nearestTeam = "";

	for (int i = 0; i < distancesData.length(); i++) {
		// Look through the distances to find distances related to the city.. and 
		if (distancesData[i].getStartingStadium() == startingTeam || distancesData[i].getEndingStadium() == startingTeam) {
			if (distancesData[i].getDistance() < shortestDistance) {
				shortestDistance = distancesData[i].getDistance();

				// Choose which city
				if (distancesData[i].getStartingStadium() != startingTeam)
					nearestTeam = distancesData[i].getStartingStadium();
				else nearestTeam = distancesData[i].getEndingStadium();
			}
			// Remove distanceData so it isn't searched for again
			distancesData.removeAt(i);
			i--;
		}
	}
	if (nearestTeam.isEmpty()) {
		qDebug() << "Could not find shortest city!";
		return;
	}
	addToTeamList(nearestTeam, shortestDistance);

	calculateShortestPlan(nearestTeam, --teamsLeft);
}



void PlanTrip::addToTeamList(QString team, double distance)
{
	//qDebug() << "Adding city: " << city << " with distance " << distance;
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
	// Remove the previous selected city
	if (tripMode == custom) {
		for (int i = 0; i < selectedTeams.length(); i++) {
			if (selectedTeams.at(i) == startingTeam) {
				selectedTeams.removeAt(i);
				break;
			}
		}
	}

	startingTeam = teamsData[index].getTeamName();
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
	//qDebug() << "Calculating for " << startingTeam << " with " << distances.length() << " cities left.";
	if (distances.length() == 0) return;
	double shortestDistance = 999999;
	QString nearestTeam = "";

	for (int i = 0; i < distances.length(); i++) {
		// Look through the distances to find distances related to the city..
		if (distances[i].getStartingStadium() == startingTeam || distances[i].getEndingStadium() == startingTeam) {
			if (distances[i].getDistance() < shortestDistance) {
				shortestDistance = distances[i].getDistance();

				// Choose which city
				if (distances[i].getStartingStadium() != startingTeam)
					nearestTeam = distances[i].getStartingStadium();
				else nearestTeam = distances[i].getEndingStadium();
			}
			// Remove distanceData so it isn't searched for again
			distances.removeAt(i);
			i--;
		}
	}
	if (nearestTeam.isEmpty()) {
		qDebug() << "Could not find shortest city!";
		return;
	}
	addToCustomTeamList(nearestTeam, shortestDistance);
	calculateCustomPlan(nearestTeam, distances);
}

// Adds or removes to the list of selected cities for the custom menu
void PlanTrip::teamToggled(bool value, QString team)
{
	if (value) {
		selectedTeams.push_back(team);
		selectedTeams.removeDuplicates();
	}
	else {
		for (int i = 0; i < selectedTeams.length(); i++) {
			if (selectedTeams.at(i) == team) {
				selectedTeams.removeAt(i);
				break;
			}
		}
	}
	// Refresh
	beginPlan();
}


// When menu is switched..
void PlanTrip::switch2nd()
{
	// Check if theres atleast 1 other city
	Database database;

	QVector<Team> teams = database.getTeams();

	ui.page_switcher->setCurrentIndex(1);
	// Fill scroll box with cities & their foods
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
	// Loop through cities to get their price and number of purchases.
	double total = 0;
	int count = 0;
	for (W_AddTeamSouvenirs* addedTeam : addedTeams) {
		total += addedTeam->getTotal();
		count += addedTeam->numOfPurchases();
	}
	ui.L_TotalCost->setText("$" + QString::number(total, 'f', 2));
	ui.L_NumberPurchasedSouvenirs->setText(QString::number(count));
}


void PlanTrip::triggerBack()
{
	ui.page_switcher->setCurrentIndex(0);
	for (int i = 0; i < addedTeams.length(); i++) {
		ui.SA_TeamList->layout()->removeWidget(addedTeams[i]);
		delete addedTeams[i];
	}
	addedTeams.clear();
	totalPriceUpdated(0);
}
