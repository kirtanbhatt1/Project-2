#include "W_TotalCount.h"

W_TotalCount::W_TotalCount(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

W_TotalCount::~W_TotalCount()
{}
void W_TotalCount::setup(int count)
{
	ui.L_Count->setText(QString::number(count));
}


void W_TotalCount::setLabelText(QString label)
{
	ui.countLabel->setText(label);
}
