#include "W_DFSList.h"

W_DFSList::W_DFSList(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

W_DFSList::~W_DFSList()
{}

void W_DFSList::setup(QString startingStadium, QString endingStadium)
{
	ui.startingStadiumLabel->setText(startingStadium);
	ui.endingStadiumLabel->setText(endingStadium);
}
