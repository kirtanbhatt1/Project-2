#include "W_SelectSouvenir.h"

W_SelectSouvenir::W_SelectSouvenir(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	QObject::connect(ui.B_AddSouvenir, &QPushButton::clicked, this, &W_SelectSouvenir::addSouvenir);
}

W_SelectSouvenir::~W_SelectSouvenir()
{}

void W_SelectSouvenir::setup(QVector<Souvenir>& souvenirs)
{
	this->souvenirs = souvenirs;

	// Combo box
	for (Souvenir souvenir : souvenirs) {
		ui.CB_AddSouvenir->addItem(souvenir.getName());
	}

	// Icon
	QPixmap pixmap("images/plus.png");
	QIcon icon(pixmap);
	ui.B_AddSouvenir->setIcon(icon);
}

void W_SelectSouvenir::addNew(Souvenir souvenir)
{
	this->souvenirs.push_back(souvenir);
	ui.CB_AddSouvenir->addItem(souvenir.getName());
}

void W_SelectSouvenir::addSouvenir()
{
	emit add(souvenirs.at(ui.CB_AddSouvenir->currentIndex()));
}
