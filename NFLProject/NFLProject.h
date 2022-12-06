#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_NFLProject.h"
#include "DisplayTeams.h"
#include "DisplaySorted.h"
#include "DisplaySouvenirs.h"


class NFLProject : public QMainWindow
{
    Q_OBJECT

public:
    NFLProject(QWidget *parent = nullptr);
    void setPage(QWidget*);
    void successfulLogin();
    void promptLogin();
    void returnMain();
    ~NFLProject();

    // Menus
    void showDisplayTeams();
    void showDisplaySorted();
    void showDisplaySouvenirs();
    void showDisplayDistances();
    void showDisplayDFS();
    void showDisplayBFS();
    void showShortestTrip();
    void showCustomTrip();

private:
    Ui::NFLProjectClass ui;
    QStackedWidget* switcher;
    QWidget* currentPage = NULL;
    QString queued = "";
    bool isLoggedIn = false;
};