#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include "maintenance.h"

//bool adminMode = false;

namespace Ui {
class Login;
}

class Login : public QMainWindow
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

private slots:
    void on_pushButton_login_clicked();

private:
    Ui::Login *ui;
    Maintenance * maintenance;
};

#endif // LOGIN_H
