#include "W_DistanceList.h"

W_DistanceList::W_DistanceList(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

W_DistanceList::~W_DistanceList()
{}
void W_DistanceList::setup(QString startingStadium,QString endingStadium, int distance)
{
	ui.startingStadiumLabel->setText(startingStadium);
	ui.endingStadiumLabel->setText(endingStadium);
	ui.distanceLabel->setText(QString::number(distance));
}