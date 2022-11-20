#ifndef MAINTENANCE_H
#define MAINTENANCE_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Maintenance; }
QT_END_NAMESPACE

class Maintenance : public QMainWindow
{
    Q_OBJECT

public:
    Maintenance(QWidget *parent = nullptr);
    ~Maintenance();

private:
    Ui::Maintenance *ui;
};
#endif // MAINTENANCE_H
