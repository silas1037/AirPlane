#ifndef USERPAN_H
#define USERPAN_H

#include <QDialog>
#include "QDebug"
#include "QMessageBox"
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QtDebug>

#include <QDate>
#include <QTime>
#include <QtPrintSupport/qprinter.h>
#include <QPrintDialog>
#include <QPrintPreviewDialog>
#include <QTextEdit>
#include <QTextDocument>
#include <QPrintPreviewWidget>
#include <QLayout>
#include <QPrintDialog>
#include <QPageSetupDialog>
#include <QPainter>
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>

namespace Ui {
class UserPan;
}

class UserPan : public QDialog
{
    Q_OBJECT

public:
    explicit UserPan(QWidget *parent = 0);
    ~UserPan();
    QString user;
    void showlist();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void printPreview2(QPrinter *p);

private:
    Ui::UserPan *ui;
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL","mysql");

    QString m_strPeintHtml;
    QString getHtmlStr();
    QPrinter *printer;
    QTextDocument *ted;
    QPrintDialog *printDlg;
    QPageSetupDialog *pageDlg;
    QPrintPreviewDialog *pd;
    QPrintPreviewWidget *preview;
    void UpdateDoc();
    void printPainter(bool isPDF,QString id,QString name,QString gender, QString age,QString mobile,QString con,QString spic1,QString spic2);
    QString getPicFile();


    QImage *image;
};

#endif // USERPAN_H
