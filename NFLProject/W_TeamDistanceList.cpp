#include "W_TeamDistanceList.h"

W_TeamDistanceList::W_TeamDistanceList(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

W_TeamDistanceList::~W_TeamDistanceList()
{}

void W_TeamDistanceList::setup(QString team, double distance)
{
	ui.L_TeamName->setText(team);
	ui.L_Distance->setText(QString::number(distance) + "km");
	this->team = team;
	this->distance = distance;
}

void W_TeamDistanceList::setup(QString startingTeam)
{
	ui.L_TeamName->setText(startingTeam);
	ui.L_Distance->setText("Distance");
	this->team = startingTeam;
	this->distance = -1;
}