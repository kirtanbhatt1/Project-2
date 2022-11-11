#pragma once

#include <QMainWindow>
#include "ui_DisplayTeams.h"
#include "W_TeamsList.h"
#include <QWidget>

class DisplayTeams : public QMainWindow
{
	Q_OBJECT

public:
	DisplayTeams(QWidget *parent = nullptr);
	~DisplayTeams();
	void initializeList();
	void open();
	void displayAllTeams();
	void clearLayout();


private:
	Ui::DisplayTeamsClass ui;
	QVector<W_TeamsList*> allWidgets;
};