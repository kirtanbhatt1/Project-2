#include "login.h"
#include "ui_login.h"
#include "NFLProject.h"
#include "Database.h"
#include "DisplayDistances.h"
#include "DisplayDFS.h"
#include <QMessageBox>

Login::Login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}

void Login::on_pushButton_login_clicked()
{
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();

    if (username == "admin" && password == "password") {
        hide();
        Maintenance * maintenance = new Maintenance(this);
        maintenance->show();
        //w.setPage(maintenance);
        qInfo() << "You entered correct user and password";
    }
    else {
        QMessageBox::warning(this, "Login", "Username and passwrod are incorrect");
    }
}
