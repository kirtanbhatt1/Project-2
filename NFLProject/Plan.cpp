#include "Plan.h"

Plan::Plan(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

Plan::~Plan()
{}


Graph Plan::getGraph()
{
	return cities;
}
void Plan::initializeEdges(QVector<Team> allCities)
{
	for (int i = 0; i < allCities.size(); i++)
	{
		getGraph().insertVertex(allCities[i].getStadium().getStadiumName());

		for (int j = 0; allCities[i].getStadium().getAllEdges().size(); j++)
		{
			getGraph().insertEdge(allCities[j].getStadium().getAllEdges()[j].getStartingStadium(), allCities[j].getStadium().getAllEdges()[j].getEndingStadium(), allCities[j].getStadium().getAllEdges()[j].getDistance());
		}
	}

}