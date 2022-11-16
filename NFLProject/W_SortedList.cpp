#include "W_SortedList.h"

W_SortedList::W_SortedList(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

W_SortedList::~W_SortedList()
{}

void W_SortedList::setup(QString teamName, QString stadium, QString capacity, QString location,
	QString roofType, QString surface, QString conference, int opened, QString division)
{
	ui.L_Name->setText(teamName);
	ui.L_Stadium->setText(stadium);
	ui.L_Capacity->setText(capacity);
	ui.L_Location->setText(location);
	ui.L_RoofType->setText(roofType);
	ui.L_Surface->setText(surface);
	ui.L_Opened->setText(QString::number(opened));
	ui.L_Division->setText(division);
	ui.L_Conference->setText(conference);
}