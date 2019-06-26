#include "userpan.h"
#include "ui_userpan.h"
#include "QDebug"

#include <QIODevice>
#include <QPaintEngine>
#include <QPrintEngine>

QString idp;
QString pname;
QString psex;
QString pphone;
QString psfz;
QString *mynoty = new QString("");

QSettings *configIniRead2 = new QSettings("./conf.ini", QSettings::IniFormat);
QString HostName2    = configIniRead2->value("/Configure/HostName").toString();
QString Port2        = configIniRead2->value("/Configure/Port").toString();
QString DatabaseName2= configIniRead2->value("/Configure/DatabaseName").toString();
QString UserName2    = configIniRead2->value("/Configure/UserName").toString();
QString Password2    = configIniRead2->value("/Configure/Password").toString();

UserPan::UserPan(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserPan)
{
    ui->setupUi(this);

    this->setWindowIcon(QIcon("1.ico"));

    //ui->label->setVisible(false);
    ui->tableWidget->setViewport(false);
    ui->textBrowser_2->setVisible(false);

    ui->textBrowser->setVisible(false);


    this->image = new QImage();





    //ui->pushButton->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;");
    ui->pushButton_2->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;");
    ui->pushButton_3->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;");
    ui->pushButton_4->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;");
    ui->pushButton_5->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;");


    this->image = new QImage();

    if(image->load("bg.jpg"))
            {
                QGraphicsScene *scene = new QGraphicsScene;
                scene->addPixmap(QPixmap::fromImage(*image));
                ui->graphicsView->setScene(scene);
                ui->graphicsView->resize(image->width() + 10, image->height() + 10);
                ui->graphicsView->show();
            }



    ted = new QTextDocument;
    printer=new QPrinter();
    printer->setOutputFormat(QPrinter::NativeFormat);
    printer->setPaperSize(QPrinter::A4);
    ted->setPageSize(printer->pageSizeMM());

    printDlg=new QPrintDialog(printer);
    pageDlg=new QPageSetupDialog(printer);

    preview = new QPrintPreviewWidget (printer,this);

    //this->ui->verticalLayout_preview->addWidget(preview);
    preview->setZoomMode(QPrintPreviewWidget::FitInView);
    connect(preview, SIGNAL(paintRequested(QPrinter*)),this,SLOT(printPreview2(QPrinter *)));//关联打印预览的内容
    //preview->show();
    preview->hide();

    UpdateDoc();
}

UserPan::~UserPan()
{
    delete ui;
}

void UserPan::on_pushButton_clicked()
{
//    ui->label->setVisible(true);
//    ui->tableWidget->setViewport(true);
}

void UserPan::showlist()//查询、刷新订单表
{
    qDebug()<<"showlist <<<<<<<<<";
    //*mynoty = new QString("");

    if (QSqlDatabase::contains("mysql")) {
        db = QSqlDatabase::database("mysql");
        qDebug()<<"mysql---";
    } else {
        db = QSqlDatabase::addDatabase("QMYSQL", "mysql");
        qDebug()<<"QMYSQL---mysql";
    }

    db.setHostName(     HostName2 + "");
    db.setPort(           Port2.toInt());
    db.setDatabaseName( DatabaseName2 + "");
    db.setUserName(      UserName2 + "");
    db.setPassword(      Password2 + "");
    bool ok = db.open();
    if(ok)  qDebug()<<"didpan sql OK";
    else qDebug()<<"didpan sql False";


    //查询姓名
    QString dia9 = new QString("select * from passenger where pid = '")+user+"';";
    qDebug()<<dia9;
    QSqlQuery querys(db);
    querys.exec(dia9);
    querys.next();
    idp = querys.value(0).toString();
    pname = querys.value(2).toString();
    psfz = querys.value(3).toString();
    pphone = querys.value(4).toString();



    ui->tableWidget->setColumnCount(9);
    ui->tableWidget->setRowCount(0); //Silas
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<" "<<"订单号"<<"航班号"<<"座位号"<<"始发地"<<"目的地"<<"起飞时间"<<"价格"<<"付款状态");

    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);  //整行选中的方式
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);   //禁止修改
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);  //设置为可以选中单个
    ui->tableWidget->verticalHeader()->setVisible(false);   //隐藏列表头

    //列宽
    ui->tableWidget->setColumnWidth(0, 20); //horizontalHeader()->set //->setResizeMode(0, QHeaderView::ResizeToContents);
//    ui->tableWidget->setColumnWidth(1, 60);
//    ui->tableWidget->setColumnWidth(2, 80);
//    ui->tableWidget->setColumnWidth(3, 80);
    ui->tableWidget->setColumnWidth(6, 145); //时间

    //查询
    QString dia = new QString("select `order`.oid,`order`.fid,`order`.sid,flight.splace,flight.eplace,`order`.ctime,`order`.price,bill.pay \
                      from flight,`order`,bill\
                      where `order`.fid=flight.fid and `order`.ctime=flight.stime and `order`.oid = bill.oid and\
                      `order`.pid = '") + user +"';";
    QSqlQuery query(db);
    query.exec(dia);

    int i = 0;
    while(query.next())
    {

        ui->textBrowser->insertPlainText("订单号：");
        ui->textBrowser->insertPlainText(query.value(0).toString());
        ui->textBrowser->insertPlainText(" 航班号：");
        ui->textBrowser->insertPlainText(query.value(1).toString());
        ui->textBrowser->insertPlainText(" 座位号：");
        ui->textBrowser->insertPlainText(query.value(2).toString());
        ui->textBrowser->insertPlainText(" 始发地：");
        ui->textBrowser->insertPlainText(query.value(3).toString());
        ui->textBrowser->insertPlainText(" 目的地：");
        ui->textBrowser->insertPlainText(query.value(4).toString());
        ui->textBrowser->insertPlainText(" 起飞时间：");
        ui->textBrowser->insertPlainText(query.value(5).toString().replace("T"," "));
        ui->textBrowser->insertPlainText(" 费用：");
        ui->textBrowser->insertPlainText(query.value(6).toString());
        ui->textBrowser->insertPlainText(" 付款状态：");
        ui->textBrowser->insertPlainText(query.value(6).toString());
        ui->textBrowser->insertPlainText("\r\n");

        mynoty->append("订单号：");
        mynoty->append(query.value(0).toString());
        mynoty->append(" 航班号：");
        mynoty->append(query.value(1).toString());
        mynoty->append(" 座位号：");
        mynoty->append(query.value(2).toString());
        mynoty->append(" 始发地：");
        mynoty->append(query.value(3).toString());
        mynoty->append(" 目的地：");
        mynoty->append(query.value(4).toString());
        mynoty->append(" 起飞时间：");
        mynoty->append(query.value(5).toString().replace("T"," "));
        mynoty->append(" 费用：");
        mynoty->append(query.value(6).toString());
        mynoty->append(" 付款状态：");
        mynoty->append((query.value(7).toString() == "1" )?"是":"否");
        mynoty->append(" \r\n ");



        //表块
        ui->tableWidget->setRowCount(i+1);
        QTableWidgetItem *check = new QTableWidgetItem();
        check->setCheckState(Qt::Unchecked);
        ui->tableWidget->setItem(i,0,check); //插入复选框

        ui->tableWidget->setItem(i,1,new QTableWidgetItem(query.value(0).toString()));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(query.value(1).toString()));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(query.value(2).toString()));
        ui->tableWidget->setItem(i,4,new QTableWidgetItem(query.value(3).toString()));
        ui->tableWidget->setItem(i,5,new QTableWidgetItem(query.value(4).toString()));
        ui->tableWidget->setItem(i,6,new QTableWidgetItem(query.value(5).toString().replace("T"," ")));
        ui->tableWidget->setItem(i,7,new QTableWidgetItem(query.value(6).toString()));
        ui->tableWidget->setItem(i,8,new QTableWidgetItem(query.value(7).toString() == "0"?"否":"是"));
        i++;
    }
    qDebug()<<*mynoty;
}
void UserPan::on_pushButton_2_clicked()//付款
{
    double money=0;


    int checkcount = 0;

    if(ui->tableWidget->rowCount() == 0)
    {
        checkcount = 0;
    }
    else
    {
        for(int i=0;i<ui->tableWidget->rowCount();i++){ //付款
            if(!ui->tableWidget->item(i,0)->checkState())
                continue;
            checkcount+=1;
        }
    }

    if(checkcount==0)
    {
        QMessageBox::critical(this ,
                    "错误" , "请勾选需要付款的机票项！",
                    QMessageBox::Ok, 0, 0);
        return;
    }

    for(int i=0;i<ui->tableWidget->rowCount();i++){ //付款
        if(!ui->tableWidget->item(i,0)->checkState())
            continue;
        if(ui->tableWidget->item(i,8)->text()=="是")
            continue;
        money+=ui->tableWidget->item(i,7)->text().toDouble();
    }
    qDebug()<<money;
    if(money == 0)
    {
        return;
    }

    bool wannapay = false;
    QMessageBox mb(QMessageBox::Information, "提示", new QString("确认支付？总共")+QString::number(money)+"元\r\n将只支付勾选订单中未支付项", QMessageBox::Yes|QMessageBox::No);
    mb.setButtonText( QMessageBox::Yes, "确认支付" );
    mb.setButtonText( QMessageBox::No, "取消支付" );
    switch( mb.exec() )
    {
        case QMessageBox::Yes:
            wannapay = true;
            qDebug()<<"sav";
            break;
        case QMessageBox::No:
            qDebug()<<"Unsav";
            break;
    }
    if(wannapay == false)
    {
        return;
    }
    for(int i=0;i<ui->tableWidget->rowCount();i++){ //付款
        if(!ui->tableWidget->item(i,0)->checkState())
            continue;
        if(ui->tableWidget->item(i,8)->text()=="是")
            continue;

        //以下执行选中框且未付款   ui->tableWidget->item(i,1)->text()

        QString oid = ui->tableWidget->item(i,1)->text();

        QString dia = new QString("select bid from bill where bill.pid = '") + user + "' and bill.oid = '" + oid + "';";
        qDebug()<<dia;

        QSqlQuery query(db);
        qDebug()<<query.exec(dia);

        query.next();
        QString bid = query.value(0).toString();
        dia = new QString("update bill set pay = true where bid = '") + bid + "';";

        qDebug()<<query.exec(dia);

        //Silas执行更新时间
        QString paytime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

        dia = new QString("update bill set ptime = '") + QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss") + "' where bid = '" + bid + "';";

        qDebug()<<query.exec(dia);


    }

    //清除check
    for(int i=0;i<ui->tableWidget->rowCount();i++){ //付款
        if(ui->tableWidget->item(i,0)->checkState())
        {
            ui->tableWidget->item(i,0)->setCheckState(Qt::Unchecked);
        }
     }

    QMessageBox box(QMessageBox::Information,"消息","支付成功！");
    box.setStandardButtons (QMessageBox::Ok);
    box.setButtonText (QMessageBox::Ok,QString("确 定"));
    box.exec ();

    showlist();



}

void UserPan::on_pushButton_3_clicked()//退单 -- 可以增加筛选"不能退订今天现在起30分钟后的之前的机票"
{
    double money=0;
    int checkcount = 0;

    if(ui->tableWidget->rowCount() == 0)
    {
        checkcount = 0;
    }
    else
    {
        for(int i=0;i<ui->tableWidget->rowCount();i++){ //付款
            if(!ui->tableWidget->item(i,0)->checkState())
                continue;
            checkcount+=1;
        }
    }

    if(checkcount==0)
    {
        QMessageBox::critical(this ,
                    "错误" , "请勾选需要退订的机票项！",
                    QMessageBox::Ok, 0, 0);
        return;
    }
    bool wannapay = false;
    QMessageBox mb(QMessageBox::Warning, "提示", "确认退订选中的订单？", QMessageBox::Yes|QMessageBox::No);
    mb.setButtonText( QMessageBox::Yes, "确认退订" );
    mb.setButtonText( QMessageBox::No, "取消退订" );
    switch( mb.exec() )
    {
        case QMessageBox::Yes:
            wannapay = true;
            qDebug()<<"sav";
            break;
        case QMessageBox::No:
            qDebug()<<"Unsav";
            break;
    }
    if(wannapay == false)
    {
        return;
    }

    //设置安全删除
    QString dia("SET SQL_SAFE_UPDATES = 0;");
    QSqlQuery query(db);
    qDebug()<<"SET SQL_SAFE_UPDATES = 0;";
    qDebug()<<query.exec(dia);



    for(int i=0;i<ui->tableWidget->rowCount();i++){ //付款
        if(!ui->tableWidget->item(i,0)->checkState())
            continue;
        if(ui->tableWidget->item(i,8)->text()=="是")
        {
            money+=ui->tableWidget->item(i,7)->text().toDouble();
        }



        //以下执行选中框   ui->tableWidget->item(i,1)->text()
        qDebug()<<"开始删除订单";

        QString oid = ui->tableWidget->item(i,1)->text();

        QString dia = new QString("delete from bill where bill.pid = '") + user + "' and bill.oid = '" + oid + "' ;";
        qDebug()<<dia;
        QSqlQuery query(db);
        qDebug()<<query.exec(dia);

        dia = new QString("delete from notify where notify.oid = '") + oid + "' ;";
        qDebug()<<dia;
        qDebug()<<query.exec(dia);

        dia = new QString("delete from `order` where pid = '") + user + "' and oid = '" + oid + "' ;";
        qDebug()<<dia;
        qDebug()<<query.exec(dia);



    }

    //清除check
    for(int i=0;i<ui->tableWidget->rowCount();i++){ //付款
        if(ui->tableWidget->item(i,0)->checkState())
        {
            ui->tableWidget->item(i,0)->setCheckState(Qt::Unchecked);
        }
     }

    QMessageBox box(QMessageBox::Information,"消息",new QString("退订成功。\r\n一共返还您")+QString::number(money)+"元。");
    box.setStandardButtons (QMessageBox::Ok);
    box.setButtonText (QMessageBox::Ok,QString("确 定"));
    box.exec ();

    showlist();
}
int pwhich = 1;
void UserPan::on_pushButton_4_clicked()//打印通知单
{
    pwhich = 1;
    ui->pushButton_4->setDisabled(true);
    ui->pushButton_5->setDisabled(true);
    //执行更新
    mynoty = new QString("");
    qDebug()<<"列数！！";
    qDebug()<<ui->tableWidget->rowCount();
    if(ui->tableWidget->rowCount()==0)
    {
        UpdateDoc();
        preview->print();

        ui->pushButton_4->setDisabled(false);
        ui->pushButton_5->setDisabled(false);
        return;
    }
    for(int i=0;i<ui->tableWidget->rowCount();i++){ //付款
        if(ui->tableWidget->item(i,0)->checkState())
        {
            //ui->tableWidget->item(i,0)->setCheckState(Qt::Unchecked);
            //ui->tableWidget->item(i,0)->text();
            mynoty->append("订单号：");
            mynoty->append(ui->tableWidget->item(i,1)->text());
            mynoty->append(" 航班号：");
            mynoty->append(ui->tableWidget->item(i,2)->text());
            mynoty->append(" 座位号：");
            mynoty->append(ui->tableWidget->item(i,3)->text());
            mynoty->append(" 始发地：");
            mynoty->append(ui->tableWidget->item(i,4)->text());
            mynoty->append(" 目的地：");
            mynoty->append(ui->tableWidget->item(i,5)->text());
            mynoty->append(" 起飞时间：");
            mynoty->append(ui->tableWidget->item(i,6)->text());
            mynoty->append(" 费用：");
            mynoty->append(ui->tableWidget->item(i,7)->text());
            mynoty->append(" 付款状态：");
            mynoty->append(ui->tableWidget->item(i,8)->text());
            mynoty->append(" \r\n ");
        }
     }
    UpdateDoc();
    preview->print();

    ui->pushButton_4->setDisabled(false);
    ui->pushButton_5->setDisabled(false);
}
void UserPan::on_pushButton_5_clicked()//打印账单
{
    ui->pushButton_4->setDisabled(true);
    ui->pushButton_5->setDisabled(true);
    double money = 0;
    pwhich = 2;

    if(ui->tableWidget->rowCount() == 0)
    {
        UpdateDoc();
        preview->print();

        ui->pushButton_4->setDisabled(false);
        ui->pushButton_5->setDisabled(false);
        return;
    }

    //执行更新
    mynoty = new QString("");
    for(int i=0;i<ui->tableWidget->rowCount();i++){ //付款
        if(ui->tableWidget->item(i,0)->checkState())
        {

            QString dia8 = new QString("select bid from bill where oid = '")+ ui->tableWidget->item(i,1)->text()+ "';";
            QSqlQuery querys(db);
            querys.exec(dia8);
            querys.next();

            mynoty->append("账单号：");
            mynoty->append(querys.value(0).toString());
            mynoty->append(" 订单号：");
            mynoty->append(ui->tableWidget->item(i,1)->text());
            mynoty->append(" 费用：");
            mynoty->append(ui->tableWidget->item(i,7)->text());
            mynoty->append(" 付款状态：");
            mynoty->append(ui->tableWidget->item(i,8)->text());
            mynoty->append(" \r\n ");

            money += ui->tableWidget->item(i,7)->text().toDouble();
        }
     }
    mynoty->append(new QString("共计：")+QString::number(money));
    UpdateDoc();
    preview->print();

    ui->pushButton_4->setDisabled(false);
    ui->pushButton_5->setDisabled(false);
}

void UserPan::UpdateDoc()
{
    ui->textBrowser_2->clear();
    ted->setHtml(getHtmlStr());
    ui->textBrowser_2->setDocument(ted);
    preview->updatePreview();
}

QString UserPan::getHtmlStr()
{
    QFile x((pwhich == 1)?":/notify_template.html":":/bill_template.html");
    x.open(QIODevice::ReadOnly);
    QTextStream in(&x);
    in.setCodec("UTF-8"); //注意编码
    QString html = in.readAll();
    {
        QString temp = (mynoty->replace("\r\n"," <p> \n"));
        qDebug()<<"now I am print??";
        m_strPeintHtml=QString(html)
                .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"))
                .arg(idp)
                .arg(pname)
                .arg(pphone)
                .arg(psfz)
                .arg(temp); //9
        //qDebug()<<m_strPeintHtml;

    }


    return m_strPeintHtml;
}
void UserPan::printPreview2(QPrinter *p)
{
    //UpdateDoc();
    ted->print(p);
}
