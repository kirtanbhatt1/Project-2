#include "W_NewSouvenir.h"

W_NewSouvenir::W_NewSouvenir(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	QObject::connect(ui.B_Remove, &QPushButton::clicked, this, &W_NewSouvenir::removeThis);
	QObject::connect(ui.SB_Amount, &QSpinBox::valueChanged, this, &W_NewSouvenir::editSouvenirAmount);
}

W_NewSouvenir::~W_NewSouvenir()
{}

void W_NewSouvenir::setup(Souvenir souvenir)
{
	ui.L_SouvenirName->setText(souvenir.getName());
	this->souvenir = souvenir;
	this->souvenir.amount = 1; // Default amount
	ui.SB_Amount->setValue(this->souvenir.amount);

	QPixmap pixmap("images/minus.png");
	QIcon icon(pixmap);
	ui.B_Remove->setIcon(icon);
}

// When the souvenir amount is changed
void W_NewSouvenir::editSouvenirAmount(int amount)
{
	souvenir.amount = amount;
	emit updated(souvenir);
}

// Removes this souvenir from the scroll box its in
void W_NewSouvenir::removeThis()
{
	emit remove(souvenir.getName());
}


