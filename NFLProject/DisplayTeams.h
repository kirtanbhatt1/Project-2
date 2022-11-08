#pragma once

#include <QMainWindow>
#include "ui_DisplayTeams.h"

class DisplayTeams : public QMainWindow
{
	Q_OBJECT

public:
	DisplayTeams(QWidget *parent = nullptr);
	~DisplayTeams();

private:
	Ui::DisplayTeamsClass ui;
};
