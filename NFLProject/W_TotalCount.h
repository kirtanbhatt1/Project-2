#pragma once

#include <QMainWindow>
#include "ui_W_TotalCount.h"

class W_TotalCount : public QMainWindow
{
	Q_OBJECT

public:
	W_TotalCount(QWidget *parent = nullptr);
	~W_TotalCount();
	void setup(int count);
	void setLabelText(QString label);

private:
	Ui::W_TotalCountClass ui;
};
