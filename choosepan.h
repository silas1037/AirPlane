#ifndef CHOOSEPAN_H
#define CHOOSEPAN_H

#include <QMainWindow>
#include "QDebug"
#include "QMessageBox"
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QtDebug>

#include "userpan.h"
#include "mythread.h"

namespace Ui {
class ChoosePan;
}

class ChoosePan : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChoosePan(QWidget *parent = 0);
    ~ChoosePan();
    QString dia;
    bool loginconfirm = true;
    bool ok;
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL","mysql");

private slots:
    void on_checkBox_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_clicked();

    void on_pushButton_4_clicked();

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_comboBox_activated(const QString &arg1);

    void on_comboBox_3_currentIndexChanged(const QString &arg1);

    void on_radioButton_4_clicked();

    void on_radioButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_9_clicked();

    void on_action_triggered();

    void on_action_2_triggered();

    void on_action_3_triggered();


    void on_action_5_triggered();

private:
    Ui::ChoosePan *ui;
    void clearall();
    QImage *image;
    MyThread *thread = new MyThread();

};

#endif // CHOOSEPAN_H
