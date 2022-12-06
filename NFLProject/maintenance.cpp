#include "maintenance.h"
#include "./ui_maintenance.h"
#include <QMessageBox>
#include <iostream>

//ADD REFRESH COMBO BOXES
//ADD ERROR CHECKING
//ADD ADMIN LOGIN

Maintenance::Maintenance(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Maintenance)
{
    ui->setupUi(this);


    NFLDatabase = QSqlDatabase::addDatabase("QSQLITE");
    NFLDatabase.setDatabaseName("C:/Users/knbha/source/repos/kirtanbhatt1/Project-2/SQLite/SQLite/NFLDatabase.db");
    NFLDatabase.open();
    if (NFLDatabase.open()) {
        std::cout << "Database is open\n";
    }
    else {
        std::cout << "Database is not open\n";
    }

    Maintenance::refresh();

}

void Maintenance::refresh(){
    QSqlQuery * db = new QSqlQuery(NFLDatabase);
    //QSqlQuery * db1 = new QSqlQuery(NFLDatabase);
    db->prepare("SELECT teamName FROM teamInfo");
    db->exec();
    ui->teamSelectSouveirCombo->clear();
    //while(db1->next()){
        while(db->next()){
            QString values = db->value("teamName").toString();
            //if(values != ""){
                ui->teamSelectSouveirCombo->addItem(values);
            //}
        }
    //}
    qInfo() << "hello";
}

Maintenance::~Maintenance()
{
    delete ui;
}

void Maintenance::on_addTeamButton_clicked()
{
    QSqlQuery * db = new QSqlQuery(NFLDatabase);
    db->prepare("SELECT * FROM teamInfo");
    db->exec();
    QString teamName = "San Diego Sailors";
    QString stadium = "Levi's Stadium";
    QString capacity = "68500";
    QString location = "Santa Clara, California";
    QString roofType = "Open";
    QString surface = "Bermuda grass / Perennial Ryegrass mixture";
    QString opened = "2014";
    QString division = "NFC West";
    QString conference = "National Football Conference";
    db->prepare("INSERT INTO teamInfo (teamName, stadium, capacity, location, roofType, surface, opened, division, conference) VALUES ('"+teamName+"','"+stadium+"','"+capacity+"','"+location+"','"+roofType+"','"+surface+"','"+opened+"','"+division+"','"+conference+"' )");
    db->exec();
    QMessageBox::information(this, "Adding New City To The Database", "San Diego Sailors added");
}


void Maintenance::on_changePriceButton_clicked()
{
    QSqlQuery * db = new QSqlQuery(NFLDatabase);

    db->prepare("SELECT * FROM teamSouvenir");
    db->exec();
    QString id;
    QString team = ui->teamSelectSouveirCombo->currentText();
    QString souv = ui->selectSouvenirCombo->currentText();
    QString price = ui->souvenirPriceInput->toPlainText();

    while (db->next() && db->value("teamName") != team) {
        qInfo() << db->value("teamName");
  }
    while (db->next() && db->value("Souvenir") != souv) {
        qInfo() << db->value("Souvenir");
        //id = QString::number((db->value("ID").toInt() + 1));
    }
    qInfo() << db->value("ID");
   id = db->value("ID").toString();
   db->prepare("UPDATE teamSouvenir SET souvenirPrice = '"+price+"' WHERE ID =  '"+id+"'");
   db->exec();
}


void Maintenance::on_addSouvenirButton_clicked()
{
    QSqlQuery* db = new QSqlQuery(NFLDatabase);
    db->prepare("SELECT teamName,Souvenir,souvenirPrice FROM newFoods");
    db->exec();
    QString team = ui->teamSelectSouveirCombo->currentText();
    QString newSou = ui->newSouvenirNameInput->toPlainText();
    QString newPrice = ui->newSouvenirPriceInput->toPlainText();
    int check = 0;
    for (int i = 0; i < newPrice.length(); i++) {
        if (newPrice[i].isDigit()) {
            check++;
        }
        else if (newPrice[i] == '.') {
            check++;
        }
    }
    if (check == newPrice.length()) {
        db->prepare("insert into teamSouvenir (teamName,Souvenir,souvenirPrice) values ('" + team + "','""','""' )");
        db->exec();
        db->prepare("insert into teamSouvenir (teamName,Souvenir,souvenirPrice) values ('""','" + newSou + "','" + newPrice + "' )");
        db->exec();
        Maintenance::refresh();
        ui->selectSouvenirCombo->update();
    }
    else {
        qInfo() << "please enter a number";
    }
   // refresh();

}

void Maintenance::on_deleteSouvenirButton_clicked()
{
    QSqlQuery * db = new QSqlQuery(NFLDatabase);
    db->prepare("SELECT * FROM teamSouvenir");
    db->exec();
    QString id;
    QString deleteSouTeam = ui->teamSelectSouveirCombo->currentText();
    QString targetSou = ui->selectSouvenirCombo->currentText();
    while(db->next() && db->value("teamName") != deleteSouTeam){
        //id = QString::number((db->value("ID").toInt() + 1));
        //qInfo() << id;
    }
    while (db->next() && db->value("Souvenir") != targetSou) {
        id = QString::number((db->value("ID").toInt() + 1));
        qInfo() << id;
    }
    id = db->value("ID").toString();
    //db->seek(0);
    db->prepare("DELETE FROM teamSouvenir WHERE ID = '"+id+"'");
    db->exec();
   // refresh();
}


void Maintenance::on_teamSelectSouveirCombo_currentTextChanged(const QString &arg1)
{
    //QString selectedSou = ui->teamSelectSouveirCombo->currentText();
    QSqlQuery * db3 = new QSqlQuery(NFLDatabase);
    QSqlQuery * db4 = new QSqlQuery(NFLDatabase);
    QSqlQuery * db5 = new QSqlQuery(NFLDatabase);
    db3->prepare("SELECT teamName,Souvenir,souvenirPrice FROM teamSouvenir");
    db3->exec();
    db4->prepare("SELECT * FROM teamInfo");
    db4->exec();
    db5->prepare("SELECT * FROM teamSouvenir");
    db5->exec();
    //while(db5->next()){
    int check = 0;
    while(db5->next()){
        if(db5->value("teamName") == arg1){
            check++;
            qInfo() << check;
        }
    }
    for(int i = 0; i < check; i++){
        while (db3->next() && db3->value("teamName") != arg1) {
            //qInfo() << db->value("city");
        }
        while (db3->next() && db3->value("Souvenir") != "") {
            QString sou = db3->value("Souvenir").toString();
            ui->selectSouvenirCombo->addItem(sou);
        }
    }

    //}
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
        //Maintenance::refresh();
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

