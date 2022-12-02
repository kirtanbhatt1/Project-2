#include "W_AddTeamSouvenirs.h"

W_AddTeamSouvenirs::W_AddTeamSouvenirs(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.SA_Souvenirs->setAlignment(Qt::AlignTop);
}

W_AddTeamSouvenirs::~W_AddTeamSouvenirs()
{}

void W_AddTeamSouvenirs::setup(Team team)
{
	ui.L_TeamName->setText(team.getTeamName());
	availableSouvenirs = team.getStadium().getSouvenirs();

	if (availableSouvenirs.length() > 0) {
		hasSelectSouvenir = true;
		selectSouvenirWidget = new W_SelectSouvenir(this);
		selectSouvenirWidget->setup(availableSouvenirs);
		ui.SA_Souvenirs->layout()->addWidget(selectSouvenirWidget);
		QObject::connect(selectSouvenirWidget, &W_SelectSouvenir::add, this, &W_AddTeamSouvenirs::triggerAddSouvenir);
	}
}

double W_AddTeamSouvenirs::getTotal()
{
	double total = 0;
	for (Souvenir souvenir: addedSouvenirs) {
		total += souvenir.getTotal();
	}
	return total;
}

int W_AddTeamSouvenirs::numOfPurchases()
{
	int count = 0;
	for (Souvenir souvenir : addedSouvenirs) {
		count += souvenir.amount;
	}
	return count;
}

void W_AddTeamSouvenirs::updateTotal()
{
	double price = getTotal();
	ui.L_Total->setText("$" + QString::number(price, 'f', 2));
	emit priceUpdated(price);
}



void W_AddTeamSouvenirs::populateSouvenirs()
{
	// Clear
	for (int i = 0; i < souvenirWidgets.length(); i++) {
		ui.SA_Souvenirs->layout()->removeWidget(souvenirWidgets.at(i));
		delete souvenirWidgets[i];
	}
	souvenirWidgets.clear();

	// Scroll box of souvenirs to add
	for (Souvenir souvenir : addedSouvenirs) {
		W_NewSouvenir* newSouvenir = new W_NewSouvenir(this);
		newSouvenir->setup(souvenir);
		souvenirWidgets.push_back(newSouvenir);
		ui.SA_Souvenirs->layout()->addWidget(newSouvenir);
	}
}

// When the combo box is updated..
void W_AddTeamSouvenirs::triggerAddSouvenir(Souvenir souvenir)
{
	// Add to bought souvenirs
	souvenir.amount = 1;
	addedSouvenirs.push(souvenir);

	// Remove from avaiable souvenirs
	for (int i = 0; i < availableSouvenirs.length(); i++) {
		if (availableSouvenirs[i].getName() == souvenir.getName()) {
			availableSouvenirs.removeAt(i);
			break;
		}
	}

	// Add souvenir to list
	addSouvenirToList(souvenir);
	updateTotal();
}

void W_AddTeamSouvenirs::addSouvenirToList(Souvenir souvenir)
{
	// Remove the add option
	if (hasSelectSouvenir) {
		ui.SA_Souvenirs->layout()->removeWidget(selectSouvenirWidget);
		delete selectSouvenirWidget;
		selectSouvenirWidget = NULL;
		hasSelectSouvenir = false;
	}

	// Add new souvenir
	W_NewSouvenir* newSouvenir = new W_NewSouvenir(this);
	newSouvenir->setup(souvenir);
	souvenirWidgets.push_back(newSouvenir);
	ui.SA_Souvenirs->layout()->addWidget(newSouvenir);
	QObject::connect(newSouvenir, &W_NewSouvenir::remove, this, &W_AddTeamSouvenirs::removeSouvenirFromList);
	QObject::connect(newSouvenir, &W_NewSouvenir::updated, this, &W_AddTeamSouvenirs::onUpdate);

	// Add the add option to the bottom (if theres any souvenirs to add)
	if (availableSouvenirs.length() > 0) {
		hasSelectSouvenir = true;
		selectSouvenirWidget = new W_SelectSouvenir(this);
		selectSouvenirWidget->setup(availableSouvenirs);
		ui.SA_Souvenirs->layout()->addWidget(selectSouvenirWidget);
		QObject::connect(selectSouvenirWidget, &W_SelectSouvenir::add, this, &W_AddTeamSouvenirs::triggerAddSouvenir);
	}
	updateTotal();
}

void W_AddTeamSouvenirs::removeSouvenirFromList(QString souvenirName)
{
	qDebug() << "Remove" << souvenirName;
	// Loop through and find the souvenir to remove
	Souvenir foundSouvenir;
	bool found = false;
	for (int i = 0; i < souvenirWidgets.length(); i++) {
		if (souvenirWidgets.at(i)->souvenir.getName() == souvenirName) {
			found = true;
			foundSouvenir = souvenirWidgets.at(i)->souvenir;
			ui.SA_Souvenirs->layout()->removeWidget(souvenirWidgets.at(i)); // or use at
			delete souvenirWidgets.at(i);
			souvenirWidgets.removeAt(i);
			break;
		}
	}

	// Remove from added souvenirs list
	for (int i = 0; i < addedSouvenirs.length(); i++) {
		if (addedSouvenirs[i].getName() == souvenirName) {
			addedSouvenirs.removeAt(i);
			break;
		}
	}

	// Add the souvenir as avaiable again
	if (!found) qDebug() << "Error: couldn't find souvenir!";
	availableSouvenirs.push_back(foundSouvenir);

	// Add the 'add option' to the box if wasn't previously there.
	if (!hasSelectSouvenir) {
		hasSelectSouvenir = true;
		selectSouvenirWidget = new W_SelectSouvenir(this);
		selectSouvenirWidget->setup(availableSouvenirs);
		ui.SA_Souvenirs->layout()->addWidget(selectSouvenirWidget);
		QObject::connect(selectSouvenirWidget, &W_SelectSouvenir::add, this, &W_AddTeamSouvenirs::triggerAddSouvenir);
	}
	else {
		// Add an option
		selectSouvenirWidget->addNew(foundSouvenir);
	}
	updateTotal();
}

void W_AddTeamSouvenirs::onUpdate(Souvenir souvenir)
{
	for (int i = 0; i < addedSouvenirs.length(); i++) {
		if (addedSouvenirs[i].getName() == souvenir.getName()) {
			addedSouvenirs[i] = souvenir;
		}
	}
	// When a souvenir is updated (i.e. amount changes)
	qDebug() << "Update" << souvenir.getName();
	updateTotal();
}
