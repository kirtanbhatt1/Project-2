#include "maintenance.h"
#include "./ui_maintenance.h"
#include <QMessageBox>

Maintenance::Maintenance(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Maintenance)
{
    ui->setupUi(this);


    NFLDatabase = QSqlDatabase::addDatabase("QSQLITE");
    NFLDatabase.setDatabaseName("C:/Users/Eric0/Desktop/Project 2/NFLDatabase.db");
    NFLDatabase.open();
    if (NFLDatabase.open()) {
        std::cout << "Database is open\n";
    }
    else {
        std::cout << "Database is not open\n";
    }


    QSqlQuery * db = new QSqlQuery(NFLDatabase);
    db->prepare("SELECT teamName FROM teamInfo");
    db->exec();
    while(db->next()){
        QString values = db->value("teamName").toString();
        if(values != ""){
            ui->teamSelectSouveirCombo->addItem(values);
        }
    }
}

Maintenance::~Maintenance()
{
    delete ui;
}

void Maintenance::on_addTeamButton_clicked()
{
    QSqlQuery * db = new QSqlQuery(NFLDatabase);
    db->exec("insert into teamInfo (teamName,stadium,capacity,location,roofType,surface,opened,division,conference) values ('""San Diego Sailors""','""Levi's Stadium""','""68500""','""Santa Clara, California""','""Open""','""Bermuda grass / Perennial Ryegrass mixture""','""2014""','""NFC West""','""National Football Conference""' )");
    QMessageBox::information(this, "Adding New City To The Database", "San Diego Sailors added");
}


void Maintenance::on_changePriceButton_clicked()
{
    QSqlQuery * db = new QSqlQuery(NFLDatabase);
    db->prepare("SELECT teamName,Souvenir,souvenirPrice FROM newFoods");
    db->exec();
    QString team = ui->teamSelectSouveirCombo->currentText();
    QString souv = ui->selectSouvenirCombo->currentText();
    QString price = ui->souvenirPriceInput->toPlainText();
    while (db->next() && db->value("teamName") != team) {
        //qInfo() << db->value("city");
  }
    while (db->next() && db->value("Souvenir") != souv) {
    }
   db->prepare("UPDATE teamInfo SET souvenirPrice = '"+price+"' WHERE teamName = '"+team+"'");
    db->exec();
}


void Maintenance::on_addSouvenirButton_clicked()
{
    QSqlQuery * db = new QSqlQuery(NFLDatabase);
    db->prepare("SELECT teamName,Souvenir,souvenirPrice FROM newFoods");
    db->exec();
    QString team = ui->teamSelectSouveirCombo->currentText();
    QString newSou = ui->newSouvenirPriceInput->toPlainText();
    QString newPrice = ui->newSouvenirNameInput->toPlainText();
    db->prepare("insert into foods (city,name,cost) values ('"+team+"','""','""' )");
    db->exec();
    db->prepare("insert into foods (city,name,cost) values ('""','"+newSou+"','"+newPrice+"' )");
    db->exec();
}


void Maintenance::on_deleteSouvenirButton_clicked()
{
    QSqlQuery * db = new QSqlQuery(NFLDatabase);
    db->prepare("SELECT * FROM teamSouvenir");
    db->exec();
    QString deleteSouTeam = ui->teamSelectSouveirCombo->currentText();
    QString targetSou = ui->selectSouvenirCombo->currentText();
    while(db->next() && db->value("teamName") != deleteSouTeam){
        //id = QString::number((db->value("id").toInt() + 1));
        //qInfo() << id;
    }
    while (db->next() && db->value("Souvenir") != targetSou) {
    }
    //id = db->value("id").toString();
    db->prepare("DELETE FROM foods WHERE Souvenir = '"+targetSou+"'");
    db->exec();
}


void Maintenance::on_teamSelectSouveirCombo_currentTextChanged(const QString &arg1)
{
    //QString selectedSou = ui->teamSelectSouveirCombo->currentText();
    QSqlQuery * db3 = new QSqlQuery(NFLDatabase);
    QSqlQuery * db4 = new QSqlQuery(NFLDatabase);
    db3->prepare("SELECT teamName,Souvenir,souvenirPrice FROM teamSouvenir");
    db3->exec();
    db4->prepare("SELECT * FROM teamInfo");
    db4->exec();
//    while(db4->next()){
        while (db3->next() && db3->value("teamName") != arg1) {
            //qInfo() << db->value("city");
        }
        while (db3->next() && db3->value("Souvenir") != "") {
            QString sou = db3->value("Souvenir").toString();
            ui->selectSouvenirCombo->addItem(sou);
        }
        while (db4->next() && db4->value("teamName") != arg1) {
            //qInfo() << db->value("city");
        }
       QString stadium = db4->value("stadium").toString();
        ui->newStadiumNameInput->setText(stadium);
       QString capacity = db4->value("capacity").toString();
        ui->newTeamCapacityInput->setText(capacity);
       QString location = db4->value("location").toString();
        ui->newLocationNameInput->setText(location);
       QString surface = db4->value("surface").toString();
        ui->newSurfaceNameInput->setText(surface);
       QString yearOpened = db4->value("opened").toString();
        ui->newYearOpenedInput->setText(yearOpened);
}


void Maintenance::on_selectSouvenirCombo_currentTextChanged(const QString &arg1)
{
    QString selectedTeam = ui->teamSelectSouveirCombo->currentText();
    QSqlQuery * db3 = new QSqlQuery(NFLDatabase);
    QSqlQuery * db4 = new QSqlQuery(NFLDatabase);
    db3->prepare("SELECT teamName,Souvenir,souvenirPrice FROM teamSouvenir");
    db3->exec();
    db4->prepare("SELECT teamName,Souvenir,souvenirPrice FROM teamSouvenir");
    db4->exec();
//    while(db4->next()){
        while (db3->next() && db3->value("teamName") != selectedTeam) {
            //qInfo() << db->value("city");
        }
        while (db3->next() && db3->value("Souvenir") != arg1) {

        }
        QString price = db3->value("souvenirPrice").toString();
        ui->souvenirPriceInput->setText(price);
//    }
}


void Maintenance::on_changeTeamInfoButton_clicked()
{
    QString targetTeam = ui->teamSelectSouveirCombo->currentText();
    QString stadium = ui->newStadiumNameInput->toPlainText();
    QString capacity = ui->newTeamCapacityInput->toPlainText();
    QString location = ui->newLocationNameInput->toPlainText();
    QString surface = ui->newSurfaceNameInput->toPlainText();
    QString yearOpened = ui->newYearOpenedInput->toPlainText();
    QString conference = ui->modifyConferenceCombo->currentText();
    QString roofType = ui->modifyRoofTypeCombo->currentText();
    QString division = ui->modifyDivisionCombo->currentText();

    QSqlQuery * db = new QSqlQuery(NFLDatabase);
    db->prepare("SELECT * FROM teamInfo");
    db->exec();
    while(db->next() && db->value("teamName") != targetTeam){
        //id = QString::number((db->value("id").toInt() + 1));
        //qInfo() << id;
    }
    //id = db->value("id").toString();
    db->prepare("UPDATE teamInfo SET stadium = '"+stadium+"',capacity = '"+capacity+"',location = '"+location+"',roofType = '"+roofType+"',surface = '"+surface+"',opened = '"+yearOpened+"',division = '"+division+"',conference = '"+conference+"' WHERE teamName = '"+targetTeam+"'");
    db->exec();
}

