#ifndef DIRPAN_H
#define DIRPAN_H

#include <QDialog>
#include "QDebug"
#include "QMessageBox"
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QtDebug>

namespace Ui {
class DirPan;
}

class DirPan : public QDialog
{
    Q_OBJECT

public:
    explicit DirPan(QWidget *parent = 0);
    ~DirPan();
    QString user;
    QSqlDatabase db; // = QSqlDatabase::addDatabase("QMYSQL","mysql");

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_clicked();

private:
    Ui::DirPan *ui;

    QImage *image;
};

#endif // DIRPAN_H
