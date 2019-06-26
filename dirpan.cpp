#include "dirpan.h"
#include "ui_dirpan.h"


bool ok;
//QString dia;
QString dia2;

QSettings *configIniRead3 = new QSettings("./conf.ini", QSettings::IniFormat);
QString HostName3    = configIniRead3->value("/Configure/HostName").toString();
QString Port3        = configIniRead3->value("/Configure/Port").toString();
QString DatabaseName3= configIniRead3->value("/Configure/DatabaseName").toString();
QString UserName3    = configIniRead3->value("/Configure/UserName").toString();
QString Password3    = configIniRead3->value("/Configure/Password").toString();

DirPan::DirPan(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DirPan)
{
    ui->setupUi(this);

    this->setWindowIcon(QIcon("1.ico"));

    this->image = new QImage();

    if(image->load("bg.jpg"))
            {
                QGraphicsScene *scene = new QGraphicsScene;
                scene->addPixmap(QPixmap::fromImage(*image));
                ui->graphicsView->setScene(scene);
                ui->graphicsView->resize(image->width() + 10, image->height() + 10);
                ui->graphicsView->show();
            }

    ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());




    db = QSqlDatabase::addDatabase("QMYSQL","mysql");
    if (QSqlDatabase::contains("mysql")) {
        db = QSqlDatabase::database("mysql");
        qDebug()<<"mysql---";
    } else {
        db = QSqlDatabase::addDatabase("QMYSQL", "mysql");
        qDebug()<<"QMYSQL---mysql";
    }

    db.setHostName(     HostName3 + "");
    db.setPort(           Port3.toInt());
    db.setDatabaseName( DatabaseName3 + "");
    db.setUserName(      UserName3 + "");
    db.setPassword(      Password3 + "");
          ok = db.open();
          if(ok)  qDebug()<<"didpan sql OK";
          else qDebug()<<"didpan sql False";


          QRegExp rx("^[0-9]{5}$");
          QRegExpValidator *pRevalidotor = new QRegExpValidator(rx, this);
          ui->lineEdit_3->setValidator(pRevalidotor);
          ui->lineEdit_3->setInputMask("000000");
          ui->lineEdit_7->setValidator(pRevalidotor);
          ui->lineEdit_7->setInputMask("000000");
}

DirPan::~DirPan()
{
    delete ui;
}


void DirPan::on_pushButton_clicked()//添加航班
{
    //1 2 4
    if(ui->lineEdit->text().trimmed().isEmpty() ||\
            ui->lineEdit_2->text().trimmed().isEmpty() ||\
            ui->lineEdit_4->text().trimmed().isEmpty())
    {
        return;
    }
    QString fid = ui->lineEdit->text();
    QString splace = ui->lineEdit_2->text();
    QString eplace = ui->lineEdit_4->text();
    QString stime = ui->dateTimeEdit->dateTime().toString("yyyy-MM-dd HH:mm");

    dia2 = new QString("INSERT INTO `flight`(`fid`, `splace`,`eplace`,`stime`) VALUES ('") +\
            fid + "','"+splace  + "','"+eplace + "','"+stime+"');";

    //INSERT INTO `flight`(`fid`, `splace`,`eplace`,`stime`) VALUES ('000001','北京','西雅图','2019-04-18 14:21:00');
    qDebug()<<dia2;
    QSqlQuery query(db);

    query.exec(dia2);

    ui->textBrowser->append("您插入了以下航班信息:");
    ui->textBrowser->append(new QString("航班号:")+fid+" 起始地:"+splace+" 目的地:"+eplace+" 起飞时间:"+stime+"\r\n");

}

void DirPan::on_pushButton_2_clicked()
{
    //3 7 5 6
    QString s1,s2;
    QString fid,price;
    if(ui->radioButton->isChecked())//单个
    {
        //qDebug()<<"radio 1";
        if(ui->lineEdit_3->text().trimmed().isEmpty() ||\
                ui->lineEdit_5->text().trimmed().isEmpty() ||\
                ui->lineEdit_6->text().trimmed().isEmpty())
        {
            return;
        }
        s1 = ui->lineEdit_3->text();
        fid = ui->lineEdit_5->text();
        price = ui->lineEdit_6->text();
        dia2 = new QString("INSERT INTO `seat`(`sid`, `fid`,`price`) VALUES ('") +\
                s1 + "','"+fid  + "','"+price+"');";

        //INSERT INTO `seat`(`sid`, `fid`,`price`) VALUES ('000001','000001',1400.5);
        qDebug()<<dia2;
        QSqlQuery query(db);

        query.exec(dia2);

        ui->textBrowser->append("您插入了以下座位信息:");
        ui->textBrowser->append(new QString("航班号:")+fid+" 座位号:"+s1+" 价格:"+price+"\r\n");


    }
    else if(ui->radioButton_2->isChecked()){
        //qDebug()<<"radio 1";
        if(ui->lineEdit_3->text().trimmed().isEmpty() ||\
                ui->lineEdit_5->text().trimmed().isEmpty() ||\
                ui->lineEdit_6->text().trimmed().isEmpty() ||\
                ui->lineEdit_7->text().trimmed().isEmpty())
        {
            return;
        }
        s1 = ui->lineEdit_3->text();
        s2 = ui->lineEdit_7->text();
        fid = ui->lineEdit_5->text();
        price = ui->lineEdit_6->text();

        if(s1.toInt() <= s2.toInt())
        {
            for(int i = s1.toInt();i<=s2.toInt();i++)
            {
                QString nextcount = QString("%1").arg(i, 6, 10, QLatin1Char('0'));
                qDebug()<<"插入:"<<nextcount;

                dia2 = new QString("INSERT INTO `seat`(`sid`, `fid`,`price`) VALUES ('") +\
                        nextcount + "','"+fid  + "','"+price+"');";

                //INSERT INTO `seat`(`sid`, `fid`,`price`) VALUES ('000001','000001',1400.5);
                qDebug()<<dia2;
                QSqlQuery query(db);

                query.exec(dia2);

                ui->textBrowser->append("您插入了以下座位信息:");
                ui->textBrowser->append(new QString("航班号:")+fid+" 座位号:"+nextcount+" 价格:"+price+"\r\n");
            }
        }
        else
        {
            for(int i = s2.toInt();i<=s1.toInt();i++)
            {
                QString nextcount = QString("%1").arg(i, 6, 10, QLatin1Char('0'));
                qDebug()<<"插入:"<<nextcount;

                dia2 = new QString("INSERT INTO `seat`(`sid`, `fid`,`price`) VALUES ('") +\
                        nextcount + "','"+fid  + "','"+price+"');";

                //INSERT INTO `seat`(`sid`, `fid`,`price`) VALUES ('000001','000001',1400.5);
                qDebug()<<dia2;
                QSqlQuery query(db);

                query.exec(dia2);

                ui->textBrowser->append("您插入了以下座位信息:");
                ui->textBrowser->append(new QString("航班号:")+fid+" 座位号:"+nextcount+" 价格:"+price+"\r\n");
            }
        }


    }

}

void DirPan::on_radioButton_2_clicked()
{
    ui->lineEdit_7->setVisible(true);
    ui->label_5->setText("起始座位号");
    ui->label_6->setVisible(true);
}

void DirPan::on_radioButton_clicked() //单个
{
    ui->lineEdit_7->setVisible(false);
    ui->label_5->setText("座位号");
    ui->label_6->setVisible(false);
}
