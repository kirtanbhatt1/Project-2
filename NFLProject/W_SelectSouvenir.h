#pragma once

#include <QWidget>
#include "ui_W_SelectSouvenir.h"
//#include "Souvenir.h"
#include "Database.h"

class W_SelectSouvenir : public QWidget
{
	Q_OBJECT

public:
	W_SelectSouvenir(QWidget *parent = nullptr);
	~W_SelectSouvenir();
	void setup(QVector<Souvenir>& souvenir);
	void addNew(Souvenir souvenir);

signals:
	void add(Souvenir souvenir);

private:
	Ui::W_SelectSouvenirClass ui;
	void addSouvenir();
	QVector<Souvenir> souvenirs;
};
