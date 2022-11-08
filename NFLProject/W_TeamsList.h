#pragma once

#include <QWidget>
#include "ui_W_TeamsList.h"

class W_TeamsList : public QWidget
{
	Q_OBJECT

public:
	W_TeamsList(QWidget *parent = nullptr);
	~W_TeamsList();

private:
	Ui::W_TeamsListClass ui;
};
