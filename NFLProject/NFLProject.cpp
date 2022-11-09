#include "NFLProject.h"

NFLProject::NFLProject(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    // Menu Bar stylesheet
     QMenuBar* menuBar = ui.menuBar;
     menuBar->setStyleSheet(
         "QMenuBar#menuBar{ background: #2B2D42; color: white; font-size: 18px; } QMenuBar::item:selected { background: #3c3f5d} QMenu{background: #474a6c} QMenu::item{background: transparent; color: white} QMenu::item:selected{background: #7478a4}"
     );
    centralWidget()->layout()->setContentsMargins(0, 0, 0, 0);
    
    // Hide status bar
    statusBar()->hide();

    // Hide main toolbar
    QToolBar* toolbar = ui.mainToolBar;
    toolbar->hide();

    // Adds an action to the menu bar and reorganizes the other menus
    QAction* homeAction = ui.menuBar->addAction("Home");
    ui.menuBar->addMenu(ui.menuDisplay);
    ui.menuBar->addMenu(ui.menuPlan);
    ui.menuBar->addMenu(ui.menuMaintenance);

    // Connections
    connect(homeAction, &QAction::triggered, this, &NFLProject::returnMain); // Return Main
    connect(ui.actionTeams, &QAction::triggered, this, &NFLProject::showDisplayTeams); // Display Cities
}

void NFLProject::returnMain()
{
    // When the main menu is requested to be shown
    ui.menuSwitcher->setCurrentIndex(0);
    if (currentPage != NULL) {
        ui.page_other->layout()->removeWidget(currentPage);
        delete currentPage;
        currentPage = NULL;
    }
}

void NFLProject::showDisplayTeams()
{
    DisplayTeams* displayTeams = new DisplayTeams(this);
    setPage(displayTeams);
    displayTeams->open();
}

void NFLProject::setPage(QWidget* page)
{
    // Clear added widget
    ui.menuSwitcher->setCurrentIndex(1);
    if (currentPage != NULL)
    {
        ui.page_other->layout()->removeWidget(currentPage);
        delete currentPage;
        currentPage = NULL;
    }

    ui.page_other->layout()->addWidget(page);
    currentPage = page;
}


NFLProject::~NFLProject()
{}
