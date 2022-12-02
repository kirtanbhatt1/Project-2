#include "PlanTrip.h"

PlanTrip::PlanTrip(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);


	//QObject::connect(ui.B_CustomNext, &QPushButton::clicked, this, &PlanTrip::switch2nd);
	//QObject::connect(ui.B_ShortestNext, &QPushButton::clicked, this, &PlanTrip::switch2nd);
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
	}
	// May have to repopulate the distances data
	//	distancesData = Database::getAllDistances();

	//	// Begin recursive search:
	//	calculateShortestPlan(startingCity, numberOfCities);
	//	ui.L_TotalDistanceShort->setText(QString::number(totalDistance) + "km");
	//}
	//else if (tripMode == custom) {
	//	// Clear data:
	//	for (int i = 0; i < w_citiesList.length(); i++) {
	//		ui.C_PlanCustom->layout()->removeWidget(w_citiesList.at(i));
	//		delete w_citiesList[i];
	//	}
	//	w_citiesList.clear();
	//	for (int i = 0; i < w_CityToggles.length(); i++) 
	//	{
	//		ui.C_PlanCities->layout()->removeWidget(w_CityToggles.at(i));
	//		delete w_CityToggles[i];
	//	}
	//	w_CityToggles.clear();

	//	// Populate CityToggles box (All cities except for the starting city)
	//	for (int i = 0; i < citiesData.length(); i++) 
	//	{
	//		if (citiesData[i].name == startingCity) continue;
	//		CityToggle* w_toggleCity = new CityToggle(this);
	//		w_toggleCity->setup(selectedCities.contains(citiesData[i].name), citiesData[i].name);
	//		QObject::connect(w_toggleCity, &CityToggle::stateChanged, this, &PlanTrip::cityToggled);
	//		w_CityToggles.push_back(w_toggleCity);
	//		ui.C_PlanCities->layout()->addWidget(w_toggleCity);
	//	}

	//	// Add starting city
	//	W_CitiesList* w_city = new W_CitiesList(this);
	//	w_city->setup(startingCity);
	//	w_citiesList.push_back(w_city);
	//	ui.C_PlanCustom->layout()->addWidget(w_city);
	//	plannedCities.push_back(startingCity);

	//	// Repopulate the data for recursive function
	//	distancesData = DbManager::getAllDistances();

	//	// Adds the selected city so its in the list of selected cities
	//	selectedCities.push_back(startingCity);
	//	selectedCities.removeDuplicates();

	//	// Remove distance data that is not of the list of selected cities.
	//	for (int i = 0; i < distancesData.length(); i++) 
	//	{
	//		if (!selectedCities.contains(distancesData[i].cityStart) || !selectedCities.contains(distancesData[i].cityEnd)) {
	//			distancesData.removeAt(i);
	//			i--;
	//		}
	//	}

	//	// Recursively populate plan cities list (should only show cities that are toggled on)
	//	calculateCustomPlan(startingCity, distancesData);
	//	ui.L_TotalDistanceCustom->setText(QString::number(totalDistance) + "km");
	//}
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
