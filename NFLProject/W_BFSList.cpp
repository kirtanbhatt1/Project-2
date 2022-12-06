#include "W_BFSList.h"

W_BFSList::W_BFSList(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

W_BFSList::~W_BFSList()
{}
void W_BFSList::setup(QString stadium)
{
	ui.stadiumNameLabel->setText(stadium);
}