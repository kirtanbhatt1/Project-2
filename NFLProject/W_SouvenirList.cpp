#include "W_SouvenirList.h"

W_SouvenirList::W_SouvenirList(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

W_SouvenirList::~W_SouvenirList()
{}

void W_SouvenirList::setup(QString item, double price)
{
	ui.itemLabel->setText(item);
	ui.priceLabel->setText("$" + QString::number(price));
}