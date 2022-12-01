#include "PlanTrip.h"

PlanTrip::PlanTrip(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

PlanTrip::~PlanTrip()
{}

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
