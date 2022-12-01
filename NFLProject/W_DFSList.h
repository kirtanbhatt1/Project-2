#pragma once

#include <QMainWindow>
#include "ui_W_DFSList.h"

class W_DFSList : public QMainWindow
{
	Q_OBJECT

public:
	W_DFSList(QWidget *parent = nullptr);
	~W_DFSList();
	void setup(QString startingStadium, QString endingStadium);

private:
	Ui::W_DFSListClass ui;
};
