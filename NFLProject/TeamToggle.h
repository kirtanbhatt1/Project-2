#pragma once

#include <QWidget>
#include "ui_TeamToggle.h"

class TeamToggle : public QWidget
{
	Q_OBJECT

public:
	TeamToggle(QWidget *parent = nullptr);
	~TeamToggle();
	void setup(bool state, QString team);
	void toggle();
	bool currentState = false;
	void setImage(bool state);

signals:
	void stateChanged(bool value, QString team);

private:
	Ui::TeamToggleClass ui;
	QString team;
};
