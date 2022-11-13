#pragma once

#include <QWidget>
#include "ui_W_SortedList.h"

class W_SortedList : public QWidget
{
	Q_OBJECT

public:
	W_SortedList(QWidget *parent = nullptr);
	~W_SortedList();

private:
	Ui::W_SortedListClass ui;
};
