#include "NFLProject.h"

NFLProject::NFLProject(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    // Menu Bar stylesheet
     QMenuBar* menuBar = ui.menuBar;
     menuBar->setStyleSheet(
         "QMenuBar#menuBar{ background: #FF5B47; color: white; font-size: 18px; } QMenuBar::item:selected { background: #616B99} QMenu{background: #668E98} QMenu::item{background: transparent; color: white} QMenu::item:selected{background: #616B99}"
     );
    centralWidget()->layout()->setContentsMargins(0, 0, 0, 0);
    
    // Hide status bar
    statusBar()->hide();

    // Hide main toolbar
    QToolBar* toolbar = ui.mainToolBar;
    toolbar->hide();

    // Add Futura font
    QFontDatabase::addApplicationFont(":/fonts/Futura Bold font");
    QFont font = QFont("Futura Bold font", 30);

}

NFLProject::~NFLProject()
{}
