#pragma once

#include <QMainWindow>
#include "ui_W_TeamName.h"

class W_TeamName : public QMainWindow
{
	Q_OBJECT

public:
	W_TeamName(QWidget *parent = nullptr);
	~W_TeamName();

private:
	Ui::W_TeamNameClass ui;
};
