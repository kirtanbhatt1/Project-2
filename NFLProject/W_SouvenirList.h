#pragma once

#include <QWidget>
#include "ui_W_SouvenirList.h"

class W_SouvenirList : public QWidget
{
	Q_OBJECT

public:
	W_SouvenirList(QWidget *parent = nullptr);
	~W_SouvenirList();
	void setup(QString item, double price);
private:
	Ui::W_SouvenirListClass ui;
};
