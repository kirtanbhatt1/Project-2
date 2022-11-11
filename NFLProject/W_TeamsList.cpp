#include "W_TeamsList.h"

W_TeamsList::W_TeamsList(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

W_TeamsList::~W_TeamsList()
{}
void W_TeamsList::setup(QString teamName, QString stadium, int capacity, QString location,
	QString roofType, QString surface, QString conference, int opened, QString division)
{
	ui.L_Name->setText(teamName);
	ui.L_Stadium->setText(stadium);
	ui.L_Capacity->setText(QString::number(capacity));
	ui.L_Location->setText(location);
	ui.L_RoofType->setText(roofType);
	ui.L_Surface->setText(surface);
	ui.L_Opened->setText(QString::number(opened));
	ui.L_Division->setText(division);
	ui.L_Conference->setText(conference);


}

