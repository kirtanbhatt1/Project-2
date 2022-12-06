#pragma once

#include <QMainWindow>
#include "ui_W_BFSList.h"

class W_BFSList : public QMainWindow
{
	Q_OBJECT

public:
	W_BFSList(QWidget *parent = nullptr);
	~W_BFSList();
	void setup(QString stadiumName);

private:
	Ui::W_BFSListClass ui;
};
