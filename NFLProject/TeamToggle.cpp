#include "TeamToggle.h"

TeamToggle::TeamToggle(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	QObject::connect(ui.B_Toggle, &QPushButton::clicked, this, &TeamToggle::toggle);
}

TeamToggle::~TeamToggle()
{}

void TeamToggle::setup(bool state, QString team)
{
	currentState = state;
	setImage(state);
	this->team = team;
	ui.L_Team->setText(team);
}

void TeamToggle::toggle()
{
	currentState = !currentState;
	setImage(currentState);
	emit stateChanged(currentState, team);
}

void TeamToggle::setImage(bool state)
{
	if (state) {
		// If true, minus symbol
		QPixmap pixmap("images/minus.png");
		QIcon icon(pixmap);
		ui.B_Toggle->setIcon(icon);
		ui.C_Items->setStyleSheet("QWidget#C_Items{ border: 3px solid lime }");
	}
	else {
		// If false, add symbol (to add it as a selected city)
		QPixmap pixmap("images/plus.png");
		QIcon icon(pixmap);
		ui.B_Toggle->setIcon(icon);
		ui.C_Items->setStyleSheet("");
	}
}
