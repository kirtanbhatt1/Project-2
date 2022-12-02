#pragma once

#include <QWidget>
#include "ui_W_NewSouvenir.h"
//#include "Souvenir.h"
#include "Database.h"

class W_NewSouvenir : public QWidget
{
	Q_OBJECT

public:
	W_NewSouvenir(QWidget *parent = nullptr);
	~W_NewSouvenir();
	void setup(Souvenir souvenir);
	Souvenir souvenir;

signals:
	void updated(Souvenir souvenir); // Called when the food amount changes
	void remove(QString souvenirName);

private:
	Ui::W_NewSouvenirClass ui;
	void editSouvenirAmount(int amount);
	void removeThis();
};