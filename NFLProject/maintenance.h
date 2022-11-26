#ifndef MAINTENANCE_H
#define MAINTENANCE_H

#include <QMainWindow>
#include <iostream>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class Maintenance; }
QT_END_NAMESPACE

class Maintenance : public QMainWindow
{
    Q_OBJECT

public:
    Maintenance(QWidget *parent = nullptr);
    ~Maintenance();
    QSqlDatabase NFLDatabase;

private slots:
    void on_addTeamButton_clicked();

    void on_changePriceButton_clicked();

    void on_addSouvenirButton_clicked();

    void on_deleteSouvenirButton_clicked();

    void on_teamSelectSouveirCombo_currentTextChanged(const QString &arg1);

    void on_selectSouvenirCombo_currentTextChanged(const QString &arg1);

    void on_changeTeamInfoButton_clicked();

private:
    Ui::Maintenance *ui;
};
#endif // MAINTENANCE_H
