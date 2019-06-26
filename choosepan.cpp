#include "choosepan.h"
#include "ui_choosepan.h"
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QtDebug>
#include "QFile"
#include "QSettings"

#include "userpan.h"
#include "dirpan.h"

QString user;
QString pass;
bool auth = true;
bool oneway = false;
bool finoneway = false;
double allpay = 0;
QString dia;



QSettings *configIniRead = new QSettings("./conf.ini", QSettings::IniFormat);
QString HostName    = configIniRead->value("/Configure/HostName").toString();
QString Port        = configIniRead->value("/Configure/Port").toString();
QString DatabaseName= configIniRead->value("/Configure/DatabaseName").toString();
QString UserName    = configIniRead->value("/Configure/UserName").toString();
QString Password    = configIniRead->value("/Configure/Password").toString();



UserPan *up2;
DirPan *dp3;

ChoosePan::ChoosePan(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChoosePan)
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

    //ui->graphicsView->setVisible(false);

    {

        ui->lineEdit->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px");
        ui->lineEdit_2->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px");
        ui->lineEdit_3->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px");
        ui->lineEdit_4->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px");
        ui->lineEdit_5->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px");
        ui->lineEdit_6->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px");
        ui->pushButton->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;");
        ui->pushButton_2->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;");
        ui->pushButton_3->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;");
        ui->pushButton_4->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;");
        ui->pushButton_5->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;");
        ui->pushButton_6->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;");
        ui->pushButton_7->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;");
        ui->pushButton_8->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;");
        ui->pushButton_9->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;");

        ui->dateEdit->setDateTime(QDateTime::currentDateTime());
    }
    //屏蔽面板
    ui->widget_2->setVisible(false);

    ui->pushButton_3->setVisible(false);
    ui->pushButton_4->setVisible(false);

    //屏蔽注册
    ui->lineEdit_3->setVisible(false);
    ui->lineEdit_4->setVisible(false);
    ui->lineEdit_5->setVisible(false);
    ui->label_3->setVisible(false);
    ui->label_4->setVisible(false);
    ui->label_5->setVisible(false);

    ui->label_8->setVisible(false);
    ui->comboBox_5->setVisible(false);

    ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
    ui->dateTimeEdit_2->setDateTime(QDateTime::currentDateTime().addDays(7));

    ui->dateTimeEdit->setMinimumDateTime(QDateTime::currentDateTime());
    ui->dateTimeEdit->setMaximumDateTime(QDateTime::currentDateTime().addDays(60));
    ui->dateTimeEdit_2->setMinimumDateTime(QDateTime::currentDateTime());
    ui->dateTimeEdit_2->setMaximumDateTime(QDateTime::currentDateTime().addDays(60));


    {
    ui->comboBox_2->insertItem(0,  "北京");
    ui->comboBox_2->insertItem(1,  "上海");
    ui->comboBox_2->insertItem(2,  "广州");
    ui->comboBox_2->insertItem(3,  "深圳");
    ui->comboBox_2->insertItem(4,  "成都");
    ui->comboBox_2->insertItem(5,  "杭州");
    ui->comboBox_2->insertItem(6,  "西安");
    ui->comboBox_2->insertItem(7,  "重庆");
    ui->comboBox_2->insertItem(8,  "青岛");
    ui->comboBox_2->insertItem(9,  "南京");
    ui->comboBox_2->insertItem(10, "厦门");
    ui->comboBox_2->insertItem(11, "昆明");
    ui->comboBox_2->insertItem(12, "大连");
    ui->comboBox_2->insertItem(13, "天津");
    ui->comboBox_2->insertItem(14, "郑州");
    ui->comboBox_2->insertItem(15, "三亚");
    ui->comboBox_2->insertItem(16, "济南");
    ui->comboBox_2->insertItem(17, "福州");

    ui->comboBox_4->insertItem(0,  "北京");
    ui->comboBox_4->insertItem(1,  "上海");
    ui->comboBox_4->insertItem(2,  "广州");
    ui->comboBox_4->insertItem(3,  "深圳");
    ui->comboBox_4->insertItem(4,  "成都");
    ui->comboBox_4->insertItem(5,  "杭州");
    ui->comboBox_4->insertItem(6,  "西安");
    ui->comboBox_4->insertItem(7,  "重庆");
    ui->comboBox_4->insertItem(8,  "青岛");
    ui->comboBox_4->insertItem(9,  "南京");
    ui->comboBox_4->insertItem(10, "厦门");
    ui->comboBox_4->insertItem(11, "昆明");
    ui->comboBox_4->insertItem(12, "大连");
    ui->comboBox_4->insertItem(13, "天津");
    ui->comboBox_4->insertItem(14, "郑州");
    ui->comboBox_4->insertItem(15, "三亚");
    ui->comboBox_4->insertItem(16, "济南");
    ui->comboBox_4->insertItem(17, "福州");
    }

    if (QSqlDatabase::contains("mysql")) {
        db = QSqlDatabase::database("mysql");
        qDebug()<<"mysql---";
    } else {
        db = QSqlDatabase::addDatabase("QMYSQL", "mysql");
        qDebug()<<"QMYSQL---mysql";
    }

//    configIniRead->value("/Configure/HostName").toString();
//    configIniRead->value("/Configure/Port").toString();
//    configIniRead->value("/Configure/DatabaseName").toString();
//    configIniRead->value("/Configure/UserName").toString();
//    configIniRead->value("/Configure/Password").toString();



          db.setHostName(     HostName + "");
          db.setPort(           Port.toInt());
          db.setDatabaseName( DatabaseName + "");
          db.setUserName(      UserName + "");
          db.setPassword(      Password + "");
          ok = db.open();
          if(ok)  qDebug()<<"OK";
          else
          {
              QMessageBox::critical(this ,
              "错误" , "数据库连接错误",
              QMessageBox::Ok, 0, 0);
              qDebug()<<"False";
          }
}

ChoosePan::~ChoosePan()
{
    delete ui;
}

void ChoosePan::on_checkBox_clicked()
{
    clearall();
    if(ui->checkBox->isChecked())
    {
        ui->radioButton->setVisible(false);
        ui->radioButton_2->setVisible(false);
        ui->pushButton->setVisible(false);
        ui->pushButton_2->setVisible(false);

        //屏蔽注册
        ui->lineEdit_3->setVisible(false);
        ui->lineEdit_4->setVisible(false);
        ui->lineEdit_5->setVisible(false);
        ui->label_3->setVisible(false);
        ui->label_4->setVisible(false);
        ui->label_5->setVisible(false);

        ui->lineEdit_2->setEchoMode(QLineEdit::Password);


        ui->pushButton_3->setVisible(true);
        ui->pushButton_4->setVisible(true);
        ui->label->setText("管理员登录");
        ui->label_2->setText("管理员密码");
    }
    else
    {
        ui->radioButton->setVisible(true);
        ui->radioButton_2->setVisible(true);
        ui->pushButton->setVisible(true);
        ui->pushButton_2->setVisible(true);
        ui->pushButton_3->setVisible(false);
        ui->pushButton_4->setVisible(false);
        ui->label->setText("登录");
        ui->label_2->setText("密码");

        //注册
        if(ui->radioButton_2->isChecked())
        {
            ui->lineEdit_3->setVisible(true);
            ui->lineEdit_4->setVisible(true);
            ui->lineEdit_5->setVisible(true);
            ui->label_3->setVisible(true);
            ui->label_4->setVisible(true);
            ui->label_5->setVisible(true);

            ui->label->setText("身份证号");
            ui->label_2->setText("电话号码");
            ui->lineEdit_2->setEchoMode(QLineEdit::Normal);
        }
        else
        {
            //屏蔽注册
            ui->lineEdit_3->setVisible(false);
            ui->lineEdit_4->setVisible(false);
            ui->lineEdit_5->setVisible(false);
            ui->label_3->setVisible(false);
            ui->label_4->setVisible(false);
            ui->label_5->setVisible(false);

            ui->label->setText("用户名");
            ui->label_2->setText("密码");
            ui->lineEdit_2->setEchoMode(QLineEdit::Password);
        }
    }
    return;
}

void ChoosePan::on_pushButton_clicked()
{

    if(ui->radioButton->isChecked())
    {
        qDebug()<<"login";
        if(ui->lineEdit->text().trimmed().isEmpty())
        {
            QMessageBox::critical(this ,
            "错误" , "请输入用户名",
            QMessageBox::Ok, 0, 0);
            return;
        }
        if(ui->lineEdit_2->text().trimmed().isEmpty()){
            QMessageBox::critical(this ,
            "错误" , "请输入密码",
            QMessageBox::Ok, 0, 0);
            return;
            }

        qDebug()<<"get sucess";

        user = ui->lineEdit->text();
        pass = ui->lineEdit_2->text();

        //构造查询.登录
        QSqlQuery query(db);

        query.exec(new QString("select pass,name from passenger where pid='")+user+"'");
        //qDebug()<<query.next()<<" "<<query.nextResult();

        //qDebug()<<query.value(0).toString();

        if(!query.next())
        {
            qDebug()<<"login not found";
            QMessageBox::critical(this ,
            "错误" , "登录失败，请检查用户名或者密码是否正确",
            QMessageBox::Ok, 0, 0);
            return;
        }
        if(pass == query.value(0).toString())
        {
            ui->widget->setVisible(false);
            ui->widget_2->setVisible(true);
            ui->tableWidget_2->setVisible(false);
            ui->label_16->setText(new QString("欢迎！")+query.value(1).toString());
            auth = 0;
            qDebug()<<"login sucess";
            //up2 = new UserPan();
        }

    }
    else if(ui->radioButton_2->isChecked())
    {
        qDebug()<<"sign up";
        int reflag = 0;
        if(ui->lineEdit->text().trimmed().isEmpty())
            reflag = 1;
        if(ui->lineEdit_2->text().trimmed().isEmpty())
            reflag = 1;
        if(ui->lineEdit_3->text().trimmed().isEmpty())
            reflag = 1;
        if(ui->lineEdit_4->text().trimmed().isEmpty())
            reflag = 1;
        if(ui->lineEdit_5->text().trimmed().isEmpty())
            reflag = 1;
        if(reflag == 1)
        {
            QMessageBox::critical(this ,
                    "错误" , "请输入完整信息",
                    QMessageBox::Ok, 0, 0);
                    return;
        }
        reflag = 0;
        if(ui->lineEdit->text().length()>18)
            reflag = 1;
        if(ui->lineEdit_2->text().length()>11)
            reflag = 1;
        if(ui->lineEdit_3->text().length()>10)
            reflag = 1;
        if(ui->lineEdit_4->text().length()>10)
            reflag = 1;
        if(ui->lineEdit_5->text().length()>10)
            reflag = 1;
        if(reflag == 1)
        {
            QMessageBox::critical(this ,
                    "错误" , "请注意字段长度",
                    QMessageBox::Ok, 0, 0);
                    return;
        }

        user = ui->lineEdit_5->text();
        pass = ui->lineEdit_4->text();
        QString name = ui->lineEdit_3->text();
        QString idcard = ui->lineEdit->text();
        QString phone = ui->lineEdit_2->text();

        //构造查询.注册
        QSqlQuery query(db);

        query.exec(new QString("select * from passenger where pid='")+user+"'");

        query.next();
        if(pass == query.value(0).toString()){
            qDebug()<<"repeat found";

            QMessageBox::critical(this ,
                    "错误" , "请使用其他用户名注册",
                    QMessageBox::Ok, 0, 0);
            }
        else
        {
            query.exec(new QString("INSERT INTO `passenger`(`pid`, `pass`,`name`,`idcard`,`phone`) VALUES ('")+ \
                                   user + "','"+pass + "','"+name + "','"+idcard + "','"+phone+"')");
            qDebug()<<new QString("INSERT INTO `passenger`(`pid`, `pass`,`name`,`idcard`,`phone`) VALUES ('")+ \
                      user + "','"+pass + "','"+name + "','"+idcard + "','"+phone+"')";
            qDebug()<<"注册成功";

            QMessageBox box(QMessageBox::Information,"消息","注册成功！");
            box.setStandardButtons (QMessageBox::Ok);
            box.setButtonText (QMessageBox::Ok,QString("确 定"));
            box.exec ();

            //INSERT INTO `passenger`(`pid`, `pass`,`name`,`idcard`,`phone`) VALUES ('000001','123','朱雀院椿','7894501','63700184');
        }
    }
    return;
}

void ChoosePan::on_pushButton_2_clicked()
{
    clearall();
}

void ChoosePan::on_pushButton_3_clicked()
{
    if(ui->checkBox->isChecked())
    {
        qDebug()<<"admin login";
        if(ui->lineEdit->text().trimmed().isEmpty())
            return;
        if(ui->lineEdit_2->text().trimmed().isEmpty())
            return;
        user = ui->lineEdit->text();
        pass = ui->lineEdit_2->text();

        //构造查询
        QSqlQuery query(db);

        query.exec(new QString("select pass from admin where aid='")+user+"'");

        //qDebug()<<query.next()<<" "<<query.nextResult();

        if(!query.next())
        {
            qDebug()<<"admin login not found";
            return;
        }
        qDebug()<<"pass input"<<pass;
        qDebug()<<query.value(0).toString();
        if(pass == query.value(0).toString())
        {
            auth = 1;
            qDebug()<<"admin login sucess";
            //dp3->db = db;
            //db.removeDatabase("QMYSQL","mysql");

            //safe remove
            QString connection;
            connection=db.connectionName(); //->connectionName();
            delete(&db);
            QSqlDatabase::removeDatabase(connection);

            dp3 = new DirPan();
            dp3->user=user;
            //dp3->db2 = QSqlDatabase::addDatabase("QMYSQL","mysql");
            this->hide();
            dp3->show();
            dp3->exec();

            //this->show();


        }
    }
    return;
}

void ChoosePan::on_radioButton_2_clicked() //sign up
{
    if(loginconfirm)
    {
        loginconfirm = false;
        clearall();
    }
    //注册
    if(ui->radioButton_2->isChecked())
    {
        ui->lineEdit_3->setVisible(true);
        ui->lineEdit_4->setVisible(true);
        ui->lineEdit_5->setVisible(true);
        ui->label_3->setVisible(true);
        ui->label_4->setVisible(true);
        ui->label_5->setVisible(true);

        ui->label->setText("身份证号");
        ui->label_2->setText("电话号码");

        ui->lineEdit_2->setEchoMode(QLineEdit::Normal);
    }
    else
    {

        //屏蔽注册
        ui->lineEdit_3->setVisible(false);
        ui->lineEdit_4->setVisible(false);
        ui->lineEdit_5->setVisible(false);
        ui->label_3->setVisible(false);
        ui->label_4->setVisible(false);
        ui->label_5->setVisible(false);

        ui->label->setText("用户名");
        ui->label_2->setText("密码");

        ui->lineEdit_2->setEchoMode(QLineEdit::Password);
    }
}

void ChoosePan::on_radioButton_clicked()
{
    if(!loginconfirm)
    {
        loginconfirm = true;
        clearall();
    }
    //注册
    if(ui->radioButton_2->isChecked())
    {

        ui->lineEdit_3->setVisible(true);
        ui->lineEdit_4->setVisible(true);
        ui->lineEdit_5->setVisible(true);
        ui->label_3->setVisible(true);
        ui->label_4->setVisible(true);
        ui->label_5->setVisible(true);

        ui->label->setText("身份证号");
        ui->label_2->setText("电话号码");
        ui->lineEdit_2->setEchoMode(QLineEdit::Normal);
    }
    else
    {
        //屏蔽注册,登录
        ui->lineEdit_3->setVisible(false);
        ui->lineEdit_4->setVisible(false);
        ui->lineEdit_5->setVisible(false);
        ui->label_3->setVisible(false);
        ui->label_4->setVisible(false);
        ui->label_5->setVisible(false);

        ui->label->setText("用户名");
        ui->label_2->setText("密码");
        ui->lineEdit_2->setEchoMode(QLineEdit::Password);
    }
}

void ChoosePan::on_pushButton_4_clicked()
{
    clearall();
}

void ChoosePan::clearall()
{
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
}

void ChoosePan::on_comboBox_currentIndexChanged(const QString &arg1)
{
    ui->comboBox_2->clear();
    if(arg1 == "热门")
    {
        ui->comboBox_2->insertItem(0,  "北京");
        ui->comboBox_2->insertItem(1,  "上海");
        ui->comboBox_2->insertItem(2,  "广州");
        ui->comboBox_2->insertItem(3,  "深圳");
        ui->comboBox_2->insertItem(4,  "成都");
        ui->comboBox_2->insertItem(5,  "杭州");
        ui->comboBox_2->insertItem(6,  "西安");
        ui->comboBox_2->insertItem(7,  "重庆");
        ui->comboBox_2->insertItem(8,  "青岛");
        ui->comboBox_2->insertItem(9,  "南京");
        ui->comboBox_2->insertItem(10, "厦门");
        ui->comboBox_2->insertItem(11, "昆明");
        ui->comboBox_2->insertItem(12, "大连");
        ui->comboBox_2->insertItem(13, "天津");
        ui->comboBox_2->insertItem(14, "郑州");
        ui->comboBox_2->insertItem(15, "三亚");
        ui->comboBox_2->insertItem(16, "济南");
        ui->comboBox_2->insertItem(17, "福州");
    }
    else if(arg1 == "ABCDE")
    {
        ui->comboBox_2->insertItem(0,  "阿尔山");
        ui->comboBox_2->insertItem(1,  "阿克苏");
        ui->comboBox_2->insertItem(2,  "阿拉善右旗");
        ui->comboBox_2->insertItem(3,  "阿拉善左旗");
        ui->comboBox_2->insertItem(4,  "阿勒泰");
        ui->comboBox_2->insertItem(5,  "阿里");
        ui->comboBox_2->insertItem(6,  "澳门");
        ui->comboBox_2->insertItem(7,  "安庆");
        ui->comboBox_2->insertItem(8,  "安顺");
        ui->comboBox_2->insertItem(9,  "鞍山");
        ui->comboBox_2->insertItem(10, "巴彦淖尔");
        ui->comboBox_2->insertItem(11, "百色");
        ui->comboBox_2->insertItem(12, "包头");
        ui->comboBox_2->insertItem(13, "保山");
        ui->comboBox_2->insertItem(14, "北海");
        ui->comboBox_2->insertItem(15, "北京");
        ui->comboBox_2->insertItem(16, "白城");
        ui->comboBox_2->insertItem(17, "白山");
        ui->comboBox_2->insertItem(18, "毕节");
        ui->comboBox_2->insertItem(19, "博乐");
        ui->comboBox_2->insertItem(20, "重庆");
        ui->comboBox_2->insertItem(21, "昌都");
        ui->comboBox_2->insertItem(22, "常德");
        ui->comboBox_2->insertItem(23, "常州");
        ui->comboBox_2->insertItem(24, "朝阳");
        ui->comboBox_2->insertItem(25, "成都");
        ui->comboBox_2->insertItem(26, "池州");
        ui->comboBox_2->insertItem(27, "赤峰");
        ui->comboBox_2->insertItem(28, "揭阳");
        ui->comboBox_2->insertItem(29, "长春");
        ui->comboBox_2->insertItem(30, "长沙");
        ui->comboBox_2->insertItem(31, "长治");
        ui->comboBox_2->insertItem(32, "承德");
        ui->comboBox_2->insertItem(33, "沧源");
        ui->comboBox_2->insertItem(34, "达县");
        ui->comboBox_2->insertItem(35, "大理");
        ui->comboBox_2->insertItem(36, "大连");
        ui->comboBox_2->insertItem(37, "大庆");
        ui->comboBox_2->insertItem(38, "大同");
        ui->comboBox_2->insertItem(39, "丹东");
        ui->comboBox_2->insertItem(40, "稻城");
        ui->comboBox_2->insertItem(41, "东营");
        ui->comboBox_2->insertItem(42, "敦煌");
        ui->comboBox_2->insertItem(43, "芒市");
        ui->comboBox_2->insertItem(44, "额济纳旗");
        ui->comboBox_2->insertItem(45, "鄂尔多斯");
        ui->comboBox_2->insertItem(46, "恩施");
        ui->comboBox_2->insertItem(47, "二连浩特");
    }
    else if(arg1 == "FGHIJ")
    {
        ui->comboBox_2->insertItem(0,  "佛山");
        ui->comboBox_2->insertItem(1,  "福州");
        ui->comboBox_2->insertItem(2,  "抚远");
        ui->comboBox_2->insertItem(3,  "阜阳");
        ui->comboBox_2->insertItem(4,  "赣州");
        ui->comboBox_2->insertItem(5,  "格尔木");
        ui->comboBox_2->insertItem(6,  "固原");
        ui->comboBox_2->insertItem(7,  "广元");
        ui->comboBox_2->insertItem(8,  "广州");
        ui->comboBox_2->insertItem(9,  "贵阳");
        ui->comboBox_2->insertItem(10, "桂林");
        ui->comboBox_2->insertItem(11, "哈尔滨");
        ui->comboBox_2->insertItem(12, "哈密");
        ui->comboBox_2->insertItem(13, "海口");
        ui->comboBox_2->insertItem(14, "海拉尔");
        ui->comboBox_2->insertItem(15, "邯郸");
        ui->comboBox_2->insertItem(16, "汉中");
        ui->comboBox_2->insertItem(17, "杭州");
        ui->comboBox_2->insertItem(18, "合肥");
        ui->comboBox_2->insertItem(19, "和田");
        ui->comboBox_2->insertItem(20, "黑河");
        ui->comboBox_2->insertItem(21, "呼和浩特");
        ui->comboBox_2->insertItem(22, "淮安");
        ui->comboBox_2->insertItem(23, "怀化");
        ui->comboBox_2->insertItem(24, "黄山");
        ui->comboBox_2->insertItem(25, "惠州");
        ui->comboBox_2->insertItem(26, "鸡西");
        ui->comboBox_2->insertItem(27, "济南");
        ui->comboBox_2->insertItem(28, "济宁");
        ui->comboBox_2->insertItem(29, "加格达奇");
        ui->comboBox_2->insertItem(30, "佳木斯");
        ui->comboBox_2->insertItem(31, "嘉峪关");
        ui->comboBox_2->insertItem(32, "金昌");
        ui->comboBox_2->insertItem(33, "金门");
        ui->comboBox_2->insertItem(34, "锦州");
        ui->comboBox_2->insertItem(35, "嘉义");
        ui->comboBox_2->insertItem(36, "西双版纳");
        ui->comboBox_2->insertItem(37, "建三江");
        ui->comboBox_2->insertItem(38, "晋江");
        ui->comboBox_2->insertItem(39, "井冈山");
        ui->comboBox_2->insertItem(40, "景德镇");
        ui->comboBox_2->insertItem(41, "九江");
        ui->comboBox_2->insertItem(42, "九寨沟");
    }
    else if(arg1 == "KLMNP")
    {
        ui->comboBox_2->insertItem(0,  "喀什");
        ui->comboBox_2->insertItem(1,  "凯里");
        ui->comboBox_2->insertItem(2,  "康定");
        ui->comboBox_2->insertItem(3,  "克拉玛依");
        ui->comboBox_2->insertItem(4,  "库车");
        ui->comboBox_2->insertItem(5,  "库尔勒");
        ui->comboBox_2->insertItem(6,  "昆明");
        ui->comboBox_2->insertItem(7,  "拉萨");
        ui->comboBox_2->insertItem(8,  "兰州");
        ui->comboBox_2->insertItem(9,  "黎平");
        ui->comboBox_2->insertItem(10, "丽江");
        ui->comboBox_2->insertItem(11, "荔波");
        ui->comboBox_2->insertItem(12, "连云港");
        ui->comboBox_2->insertItem(13, "六盘水");
        ui->comboBox_2->insertItem(14, "临汾");
        ui->comboBox_2->insertItem(15, "林芝");
        ui->comboBox_2->insertItem(16, "临沧");
        ui->comboBox_2->insertItem(17, "临沂");
        ui->comboBox_2->insertItem(18, "柳州");
        ui->comboBox_2->insertItem(19, "泸州");
        ui->comboBox_2->insertItem(20, "洛阳");
        ui->comboBox_2->insertItem(21, "吕梁");
        ui->comboBox_2->insertItem(22, "澜沧");
        ui->comboBox_2->insertItem(23, "龙岩");
        ui->comboBox_2->insertItem(24, "满洲里");
        ui->comboBox_2->insertItem(25, "梅州");
        ui->comboBox_2->insertItem(26, "绵阳");
        ui->comboBox_2->insertItem(27, "漠河");
        ui->comboBox_2->insertItem(28, "牡丹江");
        ui->comboBox_2->insertItem(29, "马祖");
        ui->comboBox_2->insertItem(30, "南昌");
        ui->comboBox_2->insertItem(31, "南充");
        ui->comboBox_2->insertItem(32, "南京");
        ui->comboBox_2->insertItem(33, "南宁");
        ui->comboBox_2->insertItem(34, "南通");
        ui->comboBox_2->insertItem(35, "南阳");
        ui->comboBox_2->insertItem(36, "宁波");
        ui->comboBox_2->insertItem(37, "宁蒗");
        ui->comboBox_2->insertItem(38, "攀枝花");
        ui->comboBox_2->insertItem(39, "普洱");
    }
    else if(arg1 == "QRSTUVW")
    {
        ui->comboBox_2->insertItem(0,  "齐齐哈尔");
        ui->comboBox_2->insertItem(1,  "黔江");
        ui->comboBox_2->insertItem(2,  "且末");
        ui->comboBox_2->insertItem(3,  "秦皇岛");
        ui->comboBox_2->insertItem(4,  "青岛");
        ui->comboBox_2->insertItem(5,  "庆阳");
        ui->comboBox_2->insertItem(6,  "衢州");
        ui->comboBox_2->insertItem(7,  "日喀则");
        ui->comboBox_2->insertItem(8,  "日照");
        ui->comboBox_2->insertItem(9,  "三亚");
        ui->comboBox_2->insertItem(10, "厦门");
        ui->comboBox_2->insertItem(11, "上海");
        ui->comboBox_2->insertItem(12, "深圳");
        ui->comboBox_2->insertItem(13, "神农架");
        ui->comboBox_2->insertItem(14, "沈阳");
        ui->comboBox_2->insertItem(15, "石家庄");
        ui->comboBox_2->insertItem(16, "塔城");
        ui->comboBox_2->insertItem(17, "台州");
        ui->comboBox_2->insertItem(18, "太原");
        ui->comboBox_2->insertItem(19, "扬州");
        ui->comboBox_2->insertItem(20, "唐山");
        ui->comboBox_2->insertItem(21, "腾冲");
        ui->comboBox_2->insertItem(22, "天津");
        ui->comboBox_2->insertItem(23, "天水");
        ui->comboBox_2->insertItem(24, "通辽");
        ui->comboBox_2->insertItem(25, "铜仁");
        ui->comboBox_2->insertItem(26, "吐鲁番");
        ui->comboBox_2->insertItem(27, "万州");
        ui->comboBox_2->insertItem(28, "威海");
        ui->comboBox_2->insertItem(29, "潍坊");
        ui->comboBox_2->insertItem(30, "温州");
        ui->comboBox_2->insertItem(31, "文山");
        ui->comboBox_2->insertItem(32, "乌海");
        ui->comboBox_2->insertItem(33, "乌兰浩特");
        ui->comboBox_2->insertItem(34, "乌鲁木齐");
        ui->comboBox_2->insertItem(35, "无锡");
        ui->comboBox_2->insertItem(36, "梧州");
        ui->comboBox_2->insertItem(37, "武汉");
        ui->comboBox_2->insertItem(38, "武夷山");
    }
    else if(arg1 == "XYZ")
    {
        ui->comboBox_2->insertItem(0,  "西安");
        ui->comboBox_2->insertItem(1,  "西昌");
        ui->comboBox_2->insertItem(2,  "西宁");
        ui->comboBox_2->insertItem(3,  "锡林浩特");
        ui->comboBox_2->insertItem(4,  "香格里拉");
        ui->comboBox_2->insertItem(5,  "襄阳");
        ui->comboBox_2->insertItem(6,  "兴义");
        ui->comboBox_2->insertItem(7,  "徐州");
        ui->comboBox_2->insertItem(8,  "香港");
        ui->comboBox_2->insertItem(9,  "烟台");
        ui->comboBox_2->insertItem(10, "延安");
        ui->comboBox_2->insertItem(11, "延吉");
        ui->comboBox_2->insertItem(12, "盐城");
        ui->comboBox_2->insertItem(13, "伊春");
        ui->comboBox_2->insertItem(14, "伊宁");
        ui->comboBox_2->insertItem(15, "宜宾");
        ui->comboBox_2->insertItem(16, "宜昌");
        ui->comboBox_2->insertItem(17, "宜春");
        ui->comboBox_2->insertItem(18, "义乌");
        ui->comboBox_2->insertItem(19, "银川");
        ui->comboBox_2->insertItem(20, "永州");
        ui->comboBox_2->insertItem(21, "榆林");
        ui->comboBox_2->insertItem(22, "玉树");
        ui->comboBox_2->insertItem(23, "运城");
        ui->comboBox_2->insertItem(24, "湛江");
        ui->comboBox_2->insertItem(25, "张家界");
        ui->comboBox_2->insertItem(26, "张家口");
        ui->comboBox_2->insertItem(27, "张掖");
        ui->comboBox_2->insertItem(28, "昭通");
        ui->comboBox_2->insertItem(29, "郑州");
        ui->comboBox_2->insertItem(30, "中卫");
        ui->comboBox_2->insertItem(31, "舟山");
        ui->comboBox_2->insertItem(32, "珠海");
        ui->comboBox_2->insertItem(33, "遵义");
    }

}

void ChoosePan::on_comboBox_activated(const QString &arg1)
{


}

void ChoosePan::on_comboBox_3_currentIndexChanged(const QString &arg1)
{
    ui->comboBox_4->clear();
    if(arg1 == "热门")
    {
        ui->comboBox_4->insertItem(0,  "北京");
        ui->comboBox_4->insertItem(1,  "上海");
        ui->comboBox_4->insertItem(2,  "广州");
        ui->comboBox_4->insertItem(3,  "深圳");
        ui->comboBox_4->insertItem(4,  "成都");
        ui->comboBox_4->insertItem(5,  "杭州");
        ui->comboBox_4->insertItem(6,  "西安");
        ui->comboBox_4->insertItem(7,  "重庆");
        ui->comboBox_4->insertItem(8,  "青岛");
        ui->comboBox_4->insertItem(9,  "南京");
        ui->comboBox_4->insertItem(10, "厦门");
        ui->comboBox_4->insertItem(11, "昆明");
        ui->comboBox_4->insertItem(12, "大连");
        ui->comboBox_4->insertItem(13, "天津");
        ui->comboBox_4->insertItem(14, "郑州");
        ui->comboBox_4->insertItem(15, "三亚");
        ui->comboBox_4->insertItem(16, "济南");
        ui->comboBox_4->insertItem(17, "福州");
    }
    else if(arg1 == "ABCDE")
    {
        ui->comboBox_4->insertItem(0,  "阿尔山");
        ui->comboBox_4->insertItem(1,  "阿克苏");
        ui->comboBox_4->insertItem(2,  "阿拉善右旗");
        ui->comboBox_4->insertItem(3,  "阿拉善左旗");
        ui->comboBox_4->insertItem(4,  "阿勒泰");
        ui->comboBox_4->insertItem(5,  "阿里");
        ui->comboBox_4->insertItem(6,  "澳门");
        ui->comboBox_4->insertItem(7,  "安庆");
        ui->comboBox_4->insertItem(8,  "安顺");
        ui->comboBox_4->insertItem(9,  "鞍山");
        ui->comboBox_4->insertItem(10, "巴彦淖尔");
        ui->comboBox_4->insertItem(11, "百色");
        ui->comboBox_4->insertItem(12, "包头");
        ui->comboBox_4->insertItem(13, "保山");
        ui->comboBox_4->insertItem(14, "北海");
        ui->comboBox_4->insertItem(15, "北京");
        ui->comboBox_4->insertItem(16, "白城");
        ui->comboBox_4->insertItem(17, "白山");
        ui->comboBox_4->insertItem(18, "毕节");
        ui->comboBox_4->insertItem(19, "博乐");
        ui->comboBox_4->insertItem(20, "重庆");
        ui->comboBox_4->insertItem(21, "昌都");
        ui->comboBox_4->insertItem(22, "常德");
        ui->comboBox_4->insertItem(23, "常州");
        ui->comboBox_4->insertItem(24, "朝阳");
        ui->comboBox_4->insertItem(25, "成都");
        ui->comboBox_4->insertItem(26, "池州");
        ui->comboBox_4->insertItem(27, "赤峰");
        ui->comboBox_4->insertItem(28, "揭阳");
        ui->comboBox_4->insertItem(29, "长春");
        ui->comboBox_4->insertItem(30, "长沙");
        ui->comboBox_4->insertItem(31, "长治");
        ui->comboBox_4->insertItem(32, "承德");
        ui->comboBox_4->insertItem(33, "沧源");
        ui->comboBox_4->insertItem(34, "达县");
        ui->comboBox_4->insertItem(35, "大理");
        ui->comboBox_4->insertItem(36, "大连");
        ui->comboBox_4->insertItem(37, "大庆");
        ui->comboBox_4->insertItem(38, "大同");
        ui->comboBox_4->insertItem(39, "丹东");
        ui->comboBox_4->insertItem(40, "稻城");
        ui->comboBox_4->insertItem(41, "东营");
        ui->comboBox_4->insertItem(42, "敦煌");
        ui->comboBox_4->insertItem(43, "芒市");
        ui->comboBox_4->insertItem(44, "额济纳旗");
        ui->comboBox_4->insertItem(45, "鄂尔多斯");
        ui->comboBox_4->insertItem(46, "恩施");
        ui->comboBox_4->insertItem(47, "二连浩特");
    }
    else if(arg1 == "FGHIJ")
    {
        ui->comboBox_4->insertItem(0,  "佛山");
        ui->comboBox_4->insertItem(1,  "福州");
        ui->comboBox_4->insertItem(2,  "抚远");
        ui->comboBox_4->insertItem(3,  "阜阳");
        ui->comboBox_4->insertItem(4,  "赣州");
        ui->comboBox_4->insertItem(5,  "格尔木");
        ui->comboBox_4->insertItem(6,  "固原");
        ui->comboBox_4->insertItem(7,  "广元");
        ui->comboBox_4->insertItem(8,  "广州");
        ui->comboBox_4->insertItem(9,  "贵阳");
        ui->comboBox_4->insertItem(10, "桂林");
        ui->comboBox_4->insertItem(11, "哈尔滨");
        ui->comboBox_4->insertItem(12, "哈密");
        ui->comboBox_4->insertItem(13, "海口");
        ui->comboBox_4->insertItem(14, "海拉尔");
        ui->comboBox_4->insertItem(15, "邯郸");
        ui->comboBox_4->insertItem(16, "汉中");
        ui->comboBox_4->insertItem(17, "杭州");
        ui->comboBox_4->insertItem(18, "合肥");
        ui->comboBox_4->insertItem(19, "和田");
        ui->comboBox_4->insertItem(20, "黑河");
        ui->comboBox_4->insertItem(21, "呼和浩特");
        ui->comboBox_4->insertItem(22, "淮安");
        ui->comboBox_4->insertItem(23, "怀化");
        ui->comboBox_4->insertItem(24, "黄山");
        ui->comboBox_4->insertItem(25, "惠州");
        ui->comboBox_4->insertItem(26, "鸡西");
        ui->comboBox_4->insertItem(27, "济南");
        ui->comboBox_4->insertItem(28, "济宁");
        ui->comboBox_4->insertItem(29, "加格达奇");
        ui->comboBox_4->insertItem(30, "佳木斯");
        ui->comboBox_4->insertItem(31, "嘉峪关");
        ui->comboBox_4->insertItem(32, "金昌");
        ui->comboBox_4->insertItem(33, "金门");
        ui->comboBox_4->insertItem(34, "锦州");
        ui->comboBox_4->insertItem(35, "嘉义");
        ui->comboBox_4->insertItem(36, "西双版纳");
        ui->comboBox_4->insertItem(37, "建三江");
        ui->comboBox_4->insertItem(38, "晋江");
        ui->comboBox_4->insertItem(39, "井冈山");
        ui->comboBox_4->insertItem(40, "景德镇");
        ui->comboBox_4->insertItem(41, "九江");
        ui->comboBox_4->insertItem(42, "九寨沟");
    }
    else if(arg1 == "KLMNP")
    {
        ui->comboBox_4->insertItem(0,  "喀什");
        ui->comboBox_4->insertItem(1,  "凯里");
        ui->comboBox_4->insertItem(2,  "康定");
        ui->comboBox_4->insertItem(3,  "克拉玛依");
        ui->comboBox_4->insertItem(4,  "库车");
        ui->comboBox_4->insertItem(5,  "库尔勒");
        ui->comboBox_4->insertItem(6,  "昆明");
        ui->comboBox_4->insertItem(7,  "拉萨");
        ui->comboBox_4->insertItem(8,  "兰州");
        ui->comboBox_4->insertItem(9,  "黎平");
        ui->comboBox_4->insertItem(10, "丽江");
        ui->comboBox_4->insertItem(11, "荔波");
        ui->comboBox_4->insertItem(12, "连云港");
        ui->comboBox_4->insertItem(13, "六盘水");
        ui->comboBox_4->insertItem(14, "临汾");
        ui->comboBox_4->insertItem(15, "林芝");
        ui->comboBox_4->insertItem(16, "临沧");
        ui->comboBox_4->insertItem(17, "临沂");
        ui->comboBox_4->insertItem(18, "柳州");
        ui->comboBox_4->insertItem(19, "泸州");
        ui->comboBox_4->insertItem(20, "洛阳");
        ui->comboBox_4->insertItem(21, "吕梁");
        ui->comboBox_4->insertItem(22, "澜沧");
        ui->comboBox_4->insertItem(23, "龙岩");
        ui->comboBox_4->insertItem(24, "满洲里");
        ui->comboBox_4->insertItem(25, "梅州");
        ui->comboBox_4->insertItem(26, "绵阳");
        ui->comboBox_4->insertItem(27, "漠河");
        ui->comboBox_4->insertItem(28, "牡丹江");
        ui->comboBox_4->insertItem(29, "马祖");
        ui->comboBox_4->insertItem(30, "南昌");
        ui->comboBox_4->insertItem(31, "南充");
        ui->comboBox_4->insertItem(32, "南京");
        ui->comboBox_4->insertItem(33, "南宁");
        ui->comboBox_4->insertItem(34, "南通");
        ui->comboBox_4->insertItem(35, "南阳");
        ui->comboBox_4->insertItem(36, "宁波");
        ui->comboBox_4->insertItem(37, "宁蒗");
        ui->comboBox_4->insertItem(38, "攀枝花");
        ui->comboBox_4->insertItem(39, "普洱");
    }
    else if(arg1 == "QRSTUVW")
    {
        ui->comboBox_4->insertItem(0,  "齐齐哈尔");
        ui->comboBox_4->insertItem(1,  "黔江");
        ui->comboBox_4->insertItem(2,  "且末");
        ui->comboBox_4->insertItem(3,  "秦皇岛");
        ui->comboBox_4->insertItem(4,  "青岛");
        ui->comboBox_4->insertItem(5,  "庆阳");
        ui->comboBox_4->insertItem(6,  "衢州");
        ui->comboBox_4->insertItem(7,  "日喀则");
        ui->comboBox_4->insertItem(8,  "日照");
        ui->comboBox_4->insertItem(9,  "三亚");
        ui->comboBox_4->insertItem(10, "厦门");
        ui->comboBox_4->insertItem(11, "上海");
        ui->comboBox_4->insertItem(12, "深圳");
        ui->comboBox_4->insertItem(13, "神农架");
        ui->comboBox_4->insertItem(14, "沈阳");
        ui->comboBox_4->insertItem(15, "石家庄");
        ui->comboBox_4->insertItem(16, "塔城");
        ui->comboBox_4->insertItem(17, "台州");
        ui->comboBox_4->insertItem(18, "太原");
        ui->comboBox_4->insertItem(19, "扬州");
        ui->comboBox_4->insertItem(20, "唐山");
        ui->comboBox_4->insertItem(21, "腾冲");
        ui->comboBox_4->insertItem(22, "天津");
        ui->comboBox_4->insertItem(23, "天水");
        ui->comboBox_4->insertItem(24, "通辽");
        ui->comboBox_4->insertItem(25, "铜仁");
        ui->comboBox_4->insertItem(26, "吐鲁番");
        ui->comboBox_4->insertItem(27, "万州");
        ui->comboBox_4->insertItem(28, "威海");
        ui->comboBox_4->insertItem(29, "潍坊");
        ui->comboBox_4->insertItem(30, "温州");
        ui->comboBox_4->insertItem(31, "文山");
        ui->comboBox_4->insertItem(32, "乌海");
        ui->comboBox_4->insertItem(33, "乌兰浩特");
        ui->comboBox_4->insertItem(34, "乌鲁木齐");
        ui->comboBox_4->insertItem(35, "无锡");
        ui->comboBox_4->insertItem(36, "梧州");
        ui->comboBox_4->insertItem(37, "武汉");
        ui->comboBox_4->insertItem(38, "武夷山");
    }
    else if(arg1 == "XYZ")
    {
        ui->comboBox_4->insertItem(0,  "西安");
        ui->comboBox_4->insertItem(1,  "西昌");
        ui->comboBox_4->insertItem(2,  "西宁");
        ui->comboBox_4->insertItem(3,  "锡林浩特");
        ui->comboBox_4->insertItem(4,  "香格里拉");
        ui->comboBox_4->insertItem(5,  "襄阳");
        ui->comboBox_4->insertItem(6,  "兴义");
        ui->comboBox_4->insertItem(7,  "徐州");
        ui->comboBox_4->insertItem(8,  "香港");
        ui->comboBox_4->insertItem(9,  "烟台");
        ui->comboBox_4->insertItem(10, "延安");
        ui->comboBox_4->insertItem(11, "延吉");
        ui->comboBox_4->insertItem(12, "盐城");
        ui->comboBox_4->insertItem(13, "伊春");
        ui->comboBox_4->insertItem(14, "伊宁");
        ui->comboBox_4->insertItem(15, "宜宾");
        ui->comboBox_4->insertItem(16, "宜昌");
        ui->comboBox_4->insertItem(17, "宜春");
        ui->comboBox_4->insertItem(18, "义乌");
        ui->comboBox_4->insertItem(19, "银川");
        ui->comboBox_4->insertItem(20, "永州");
        ui->comboBox_4->insertItem(21, "榆林");
        ui->comboBox_4->insertItem(22, "玉树");
        ui->comboBox_4->insertItem(23, "运城");
        ui->comboBox_4->insertItem(24, "湛江");
        ui->comboBox_4->insertItem(25, "张家界");
        ui->comboBox_4->insertItem(26, "张家口");
        ui->comboBox_4->insertItem(27, "张掖");
        ui->comboBox_4->insertItem(28, "昭通");
        ui->comboBox_4->insertItem(29, "郑州");
        ui->comboBox_4->insertItem(30, "中卫");
        ui->comboBox_4->insertItem(31, "舟山");
        ui->comboBox_4->insertItem(32, "珠海");
        ui->comboBox_4->insertItem(33, "遵义");
    }
}

void ChoosePan::on_radioButton_4_clicked() //单程
{
    oneway = true;
    if(ui->radioButton_4->isChecked())
    {
        ui->dateTimeEdit_2->setVisible(false);
        ui->label_10->setVisible(false);
    }
}

void ChoosePan::on_radioButton_3_clicked()
{
    oneway = false;
    if(ui->radioButton_3->isChecked())
    {
        ui->dateTimeEdit_2->setVisible(true);
        ui->label_10->setVisible(true);
    }
}

void ChoosePan::on_pushButton_5_clicked() //查询
{
    //QString dia;
    QString sday;
    QString eday;
    QString scity;
    QString ecity;
    QString count;
    QString price;
    if(oneway) //单程查询
    {
        finoneway = true;
        ui->tableWidget->setGeometry(QRect(10,150,541,361)); //10,150,461,361
        ui->tableWidget_2->setVisible(false);

        if(ui->comboBox_2->currentText() == ui->comboBox_4->currentText())
        {
            QMessageBox::critical(this ,
            "错误" , "出发城市和目的城市不应该相同！",
            QMessageBox::Ok, 0, 0);
            return;
        }

        sday = ui->dateTimeEdit->dateTime().toString("yyyy-MM-dd");
        scity = ui->comboBox_2->currentText();
        ecity = ui->comboBox_4->currentText();

        qDebug()<<"check oneway datetime ok";

        dia = new QString("select * from flight where splace = '"+scity+"' and eplace = '"+ecity+"' and date_format(stime,'%Y-%m-%d') = '") + sday + "'";

        //qDebug()<<dia;
        qDebug()<<"单程";

        QSqlQuery query(db);

        query.exec(dia);

        QString fid;
        QString splace;
        QString eplace;
        QString stime;

        ui->tableWidget->setColumnCount(6);
        ui->tableWidget->setRowCount(0);
        ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<" "<<"航班号"<<"始发地"<<"目的地"<<"起飞时间"<<"最低价(元)");

        ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);  //整行选中的方式
        ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);   //禁止修改
        ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);  //设置为可以选中单个
        ui->tableWidget->verticalHeader()->setVisible(false);   //隐藏列表头

        //列宽
        ui->tableWidget->setColumnWidth(0, 20); //horizontalHeader()->set //->setResizeMode(0, QHeaderView::ResizeToContents);
        ui->tableWidget->setColumnWidth(1, 60);
        ui->tableWidget->setColumnWidth(2, 80);
        ui->tableWidget->setColumnWidth(3, 80);
        ui->tableWidget->setColumnWidth(4, 145);

        int i = 0;
        while(query.next())
        {
            fid = query.value(0).toString();
            splace = query.value(1).toString();
            eplace = query.value(2).toString();
            stime = query.value(3).toString();

            //座位剩余数查询

            dia = new QString("select count(distinct(`seat`.sid))\
            from `seat`\
            where \
            seat.fid = '")+ fid +"' and \
            seat.sid not in \
            (\
            select `order`.sid\
            from `order`\
            where \
            `order`.fid = '"+fid+"' and\
            date_format(ctime,'%Y-%m-%d') = '"+sday+"');";

            //qDebug()<<dia;

            QSqlQuery query2(db);

            query2.exec(dia);
            query2.next();
            count = query2.value(0).toString();
            qDebug()<< count;
            qDebug()<< count.toInt();
            if(count.toInt()>0)
            {
                //最低票价
                dia = new QString("select min(`seat`.price)\
                from `seat`\
                where \
                seat.fid = '")+ fid +"' and \
                seat.sid not in \
                (\
                select `order`.sid\
                from `order`\
                where \
                `order`.fid = '"+fid+"' and\
                date_format(ctime,'%Y-%m-%d') = '"+sday+"');";

                //qDebug()<<dia;

                QSqlQuery query2(db);

                query2.exec(dia);
                query2.next();
                price = query2.value(0).toString();
                qDebug()<< price;
                qDebug()<< price.toDouble();


                ui->tableWidget->setRowCount(i+1);
                QTableWidgetItem *check = new QTableWidgetItem();
                check->setCheckState(Qt::Unchecked);
                ui->tableWidget->setItem(i,0,check); //插入复选框

                ui->tableWidget->setItem(i,1,new QTableWidgetItem(fid));
                ui->tableWidget->setItem(i,2,new QTableWidgetItem(splace));
                ui->tableWidget->setItem(i,3,new QTableWidgetItem(eplace));
                ui->tableWidget->setItem(i,4,new QTableWidgetItem(stime.replace("T"," ")));
                ui->tableWidget->setItem(i,5,new QTableWidgetItem(price));
                i++;
            }


        }

        //select * from flight where date_format(stime,'%Y-%m-%d') = '2019-04-20'
    }
    else //双程
    {
        finoneway = false;
        ui->tableWidget->setGeometry(QRect(10,150,541,181)); //10,150,461,361
        ui->tableWidget_2->setVisible(true);
        if(ui->comboBox_2->currentText() == ui->comboBox_4->currentText())
        {
            QMessageBox::critical(this ,
            "错误" , "出发城市和目的城市不应该相同！",
            QMessageBox::Ok, 0, 0);
            return;
        }
        if(ui->dateTimeEdit->dateTime().operator >(ui->dateTimeEdit_2->dateTime()))//不能用>=因为当天往返也有
        {
            QMessageBox::critical(this ,
            "错误" , "双程查询时去程日期不应该大于返程日期！",
            QMessageBox::Ok, 0, 0);
            return;
        }
        qDebug()<<"check datetime ok";

        sday = ui->dateTimeEdit->dateTime().toString("yyyy-MM-dd");
        eday = ui->dateTimeEdit_2->dateTime().toString("yyyy-MM-dd");
        scity = ui->comboBox_2->currentText();
        ecity = ui->comboBox_4->currentText();


        //表一
        ui->tableWidget->setColumnCount(6);
        ui->tableWidget->setRowCount(0);
        ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<" "<<"航班号"<<"始发地"<<"目的地"<<"起飞时间"<<"最低价(元)");

        ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);  //整行选中的方式
        ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);   //禁止修改
        ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);  //设置为可以选中单个
        ui->tableWidget->verticalHeader()->setVisible(false);   //隐藏列表头

        //列宽
        ui->tableWidget->setColumnWidth(0, 20); //horizontalHeader()->set //->setResizeMode(0, QHeaderView::ResizeToContents);
        ui->tableWidget->setColumnWidth(1, 60);
        ui->tableWidget->setColumnWidth(2, 80);
        ui->tableWidget->setColumnWidth(3, 80);
        ui->tableWidget->setColumnWidth(4, 145);

        //表二
        ui->tableWidget_2->setColumnCount(6);
        ui->tableWidget_2->setRowCount(0);
        ui->tableWidget_2->setHorizontalHeaderLabels(QStringList()<<" "<<"航班号"<<"始发地"<<"目的地"<<"起飞时间"<<"最低价(元)");

        ui->tableWidget_2->setSelectionBehavior(QAbstractItemView::SelectRows);  //整行选中的方式
        ui->tableWidget_2->setEditTriggers(QAbstractItemView::NoEditTriggers);   //禁止修改
        ui->tableWidget_2->setSelectionMode(QAbstractItemView::SingleSelection);  //设置为可以选中单个
        ui->tableWidget_2->verticalHeader()->setVisible(false);   //隐藏列表头

        //列宽
        ui->tableWidget_2->setColumnWidth(0, 20); //horizontalHeader()->set //->setResizeMode(0, QHeaderView::ResizeToContents);
        ui->tableWidget_2->setColumnWidth(1, 60);
        ui->tableWidget_2->setColumnWidth(2, 80);
        ui->tableWidget_2->setColumnWidth(3, 80);
        ui->tableWidget_2->setColumnWidth(4, 145);



        //查询A
        dia = new QString("select * from flight where splace = '")+scity+"' and eplace = '"+ecity+"' and date_format(stime,'%Y-%m-%d') = '" + sday + "'";

        qDebug()<<"双程A";

        QSqlQuery query(db);

        query.exec(dia);

        //结果准备
        QString fid;
        QString splace;
        QString eplace;
        QString stime;

        int i = 0;
        while(query.next())
        {
            fid = query.value(0).toString();
            splace = query.value(1).toString();
            eplace = query.value(2).toString();
            stime = query.value(3).toString();

            //座位剩余数查询

            dia = new QString("select count(distinct(`seat`.sid))\
            from `seat`\
            where \
            seat.fid = '")+ fid +"' and \
            seat.sid not in \
            (\
            select `order`.sid\
            from `order`\
            where \
            `order`.fid = '"+fid+"' and\
            date_format(ctime,'%Y-%m-%d') = '"+sday+"');";

            //qDebug()<<dia;

            QSqlQuery query2(db);

            query2.exec(dia);
            query2.next();
            count = query2.value(0).toString();
            qDebug()<< count;
            qDebug()<< count.toInt();

            if(count.toInt()>0)
            {
                //最低票价
                dia = new QString("select min(`seat`.price)\
                from `seat`\
                where \
                seat.fid = '")+ fid +"' and \
                seat.sid not in \
                (\
                select `order`.sid\
                from `order`\
                where \
                `order`.fid = '"+fid+"' and\
                date_format(ctime,'%Y-%m-%d') = '"+sday+"');";

                //qDebug()<<dia;

                QSqlQuery query2(db);

                query2.exec(dia);
                query2.next();
                price = query2.value(0).toString();
                qDebug()<< price;
                qDebug()<< price.toDouble();




                ui->tableWidget->setRowCount(i+1);
                QTableWidgetItem *check = new QTableWidgetItem();
                check->setCheckState(Qt::Unchecked);
                ui->tableWidget->setItem(i,0,check); //插入复选框

                ui->tableWidget->setItem(i,1,new QTableWidgetItem(fid));
                ui->tableWidget->setItem(i,2,new QTableWidgetItem(splace));
                ui->tableWidget->setItem(i,3,new QTableWidgetItem(eplace));
                ui->tableWidget->setItem(i,4,new QTableWidgetItem(stime.replace("T"," ")));
                ui->tableWidget->setItem(i,5,new QTableWidgetItem(price));
                i++;
            }

        }

        //查询B bug多。
                dia = new QString("select * from flight where splace = '")+ecity+"' and eplace = '"+scity+"' and date_format(stime,'%Y-%m-%d') = '" + eday + "'";

                qDebug()<<"双程B";

                QSqlQuery query3(db);

                query3.exec(dia);
                i = 0;
                while(query3.next())
                {
                    fid = query3.value(0).toString();
                    splace = query3.value(1).toString();
                    eplace = query3.value(2).toString();
                    stime = query3.value(3).toString();

                    //座位剩余数查询

                    dia = new QString("select count(distinct(`seat`.sid))\
                    from `seat`\
                    where \
                    seat.fid = '")+ fid +"' and \
                    seat.sid not in \
                    (\
                    select `order`.sid\
                    from `order`\
                    where \
                    `order`.fid = '"+fid+"' and\
                    date_format(ctime,'%Y-%m-%d') = '"+eday+"');"; //Silas bug

                    //qDebug()<<dia;

                    QSqlQuery query2(db);

                    query2.exec(dia);
                    query2.next();
                    count = query2.value(0).toString();
                    qDebug()<< count;
                    qDebug()<< count.toInt();

                    if(count.toInt()>0)
                    {
                        //最低票价
                        dia = new QString("select min(`seat`.price)\
                        from `seat`\
                        where \
                        seat.fid = '")+ fid +"' and \
                        seat.sid not in \
                        (\
                        select `order`.sid\
                        from `order`\
                        where \
                        `order`.fid = '"+fid+"' and\
                        date_format(ctime,'%Y-%m-%d') = '"+eday+"');";//Silas bug

                        //qDebug()<<dia;

                        QSqlQuery query2(db);

                        query2.exec(dia);
                        query2.next();
                        price = query2.value(0).toString();
                        qDebug()<< price;
                        qDebug()<< price.toDouble();





                        ui->tableWidget_2->setRowCount(i+1);
                        QTableWidgetItem *check = new QTableWidgetItem();
                        check->setCheckState(Qt::Unchecked);
                        ui->tableWidget_2->setItem(i,0,check); //插入复选框

                        ui->tableWidget_2->setItem(i,1,new QTableWidgetItem(fid));
                        ui->tableWidget_2->setItem(i,2,new QTableWidgetItem(splace));
                        ui->tableWidget_2->setItem(i,3,new QTableWidgetItem(eplace));
                        ui->tableWidget_2->setItem(i,4,new QTableWidgetItem(stime.replace("T"," ")));
                        ui->tableWidget_2->setItem(i,5,new QTableWidgetItem(price));
                        i++;

                    }
                }

    }
}

void ChoosePan::on_pushButton_6_clicked() //订票
{
    //取票标记
    bool rushflag = false;

    QString nextcount=0;
    QString dia;
    allpay=0;
    QString notfid;
    if(finoneway)//单程
    {
        for(int i=0;i<ui->tableWidget->rowCount();i++){//以下在查询有勾选时执行，可以只添加订单和账单，但是不支付
            if(!ui->tableWidget->item(i,0)->checkState())
                continue;

            //qDebug()<<ui->tableWidget->item(i,5)->text();

            //记账
            allpay+=ui->tableWidget->item(i,5)->text().toDouble();
            qDebug()<<allpay;

            //查询订单数
            //QString dia;
            QString dia("select count(*) from `order`;");
            QSqlQuery query4(db);
            query4.exec(dia);
            query4.next();

//            //QString nextcount(query4.value(0).toInt()+1);
//            qDebug()<<query4.value(0).toInt();

//            QString nextcount = QString("%1").arg(query4.value(0).toInt()+1, 6, 10, QLatin1Char('0'));
//            //nextcount=nextcount.replace("\u","00");
//            qDebug()<<"现在计数"<<nextcount;


            //先构造fid
            QString fid = ui->tableWidget->item(i,1)->text();//表


            //下一个座位
            QString sday = ui->dateTimeEdit->dateTime().toString("yyyy-MM-dd"); //silas


            QString nextseat;
            dia = new QString("select distinct(`seat`.sid),price\
            from `seat`\
            where \
            seat.fid = '")+ fid +"' and \
            seat.sid not in \
            (\
            select `order`.sid\
            from `order`\
            where \
            `order`.fid = '"+fid+"' and\
            date_format(ctime,'%Y-%m-%d') = '"+sday+"');";

            //qDebug()<<dia;

            QSqlQuery query2(db);

            query2.exec(dia);

            if(query2.next()==false) //有没有下一个座位
            {
                rushflag = true;
                continue;
            }

            nextseat = query2.value(0).toString();
            qDebug()<< "下一个座位:"<<nextseat;
            //qDebug()<< count.toInt();




            QString sid = nextseat;//查询
            QString pid = user;
            QString price = ui->tableWidget->item(i,5)->text();//表
            QString ctime = ui->tableWidget->item(i,4)->text();//表

            //查询下一个订单号,为了避免前面已经删除，应该筛选最大值

            QString nextoid;

            //dia = new QString("select max(oid) from `order`;");

            QSqlQuery query(db);
order1:
            qDebug()<<query.exec("select oid from `order`;");

            if(query.next() == false)
            {
                nextoid = "000001";
                qDebug()<<"订单号无";
            }
            else
            {
                qDebug()<<"订单号有";
                query.exec("select max(oid) from `order`;");
                query.next(); //Silas
                nextoid = QString("%1").arg(query.value(0).toInt()+1, 6, 10, QLatin1Char('0')); //query.value(0).toInt();
            }

            //添加订单 注意查询订单号 而且循环保证插入成功
            dia = new QString("INSERT INTO `order`(`oid`, `fid`,`sid`,`pid`, `price`,`ctime`) VALUES('")+ nextoid +\
                     "','" + fid + "','" + sid + "','" +pid + "'," +price + ",'" + ctime.replace("T"," ") + "');";

            //INSERT INTO `order`(`oid`, `fid`,`sid`,`pid`, `price`,`ctime`) VALUES('000001','000001','000001','000003',1400.5,'2019-04-18 14:21:00');
            //qDebug()<<"添加订单A"<<dia;

            qDebug()<<"添加订单情况";

            if(query.exec(dia)==false)
            {
                goto order1;
            }




notify1:

            //添加通知单
            //QSqlQuery query(db);

            qDebug()<<query.exec("select nid from notify;");

            bool hav = query.next(); //false

            qDebug()<<"添加通知单";

            if(hav)
            {
                qDebug()<<"通知号有";

                query.exec("select max(nid) from notify;");

                query.next(); //Silas

                QString nextnid = QString("%1").arg(query.value(0).toInt()+1, 6, 10, QLatin1Char('0'));

                if(query.exec(new QString("insert into `notify` values('") + nextnid +"','"+nextoid + "');")==false)
                {
                    goto notify1;
                }
            }
            else
            {
                qDebug()<<"通知号无";

                if(query.exec(new QString("insert into `notify` values('000001','")+nextoid + "');")==false)
                {
                    goto notify1;
                }
                //insert into `notify` values('000001','000001')
            }




billagain1:


            //添加账单
            qDebug()<<query.exec("select bid from bill;");

            hav = query.next(); //false

            qDebug()<<"添加账单";

            if(hav)
            {

                qDebug()<<"账单号有";

                query.exec("select max(bid) from bill;");

                query.next(); //Silas

                QString nextbid = QString("%1").arg(query.value(0).toInt()+1, 6, 10, QLatin1Char('0'));

                dia = new QString("insert into `bill`(`bid`,`oid`,`pid`,`price`,`pay`,`ptime`) values('") +\
                        nextbid +"','"+nextoid+"','"+pid+"',"+price+","+"false"+","+"null" + ");";

                qDebug()<<"账单语句"<<dia;

                if(query.exec(dia)==false) //silas并发控制
                {
                    goto billagain1;
                }

                //insert into `bill`(`bid`,`oid`,`pid`,`price`,`pay`,`ptime`) values('000001','000001','000001','4410.5',true,'2019-04-18 14:21:00')
            }
            else
            {
                qDebug()<<"账单号无";

                dia = new QString("insert into `bill`(`bid`,`oid`,`pid`,`price`,`pay`,`ptime`) values('000001','") +\
                        nextoid+"','"+pid+"',"+price+","+"false"+","+"null" + ");";
                qDebug()<<"账单语句"<<dia;

                if(query.exec(dia)==false)
                {
                    goto billagain1;
                }
                //qDebug()<<query.exec(new QString("insert into `notify` values('000001','")+nextoid + "');");
                //insert into `notify` values('000001','000001')
            }


        }//end for
    }
    else //双程
    {
        for(int i=0;i<ui->tableWidget->rowCount();i++){ //双程去
            if(!ui->tableWidget->item(i,0)->checkState())
                continue;

            qDebug()<<ui->tableWidget->item(i,5)->text();

            allpay+=ui->tableWidget->item(i,5)->text().toDouble();

//            //查询订单数
//            //QString dia;
//            QString dia("select count(*) from `order`;");
//            QSqlQuery query4(db);
//            query4.exec(dia);
//            query4.next();

//            //QString nextcount(query4.value(0).toInt()+1);
//            qDebug()<<query4.value(0).toInt();

//            QString nextcount = QString("%1").arg(query4.value(0).toInt()+1, 6, 10, QLatin1Char('0'));
//            //nextcount=nextcount.replace("\u","00");
//            qDebug()<<"现在计数"<<nextcount;


            //先构造fid
            QString fid = ui->tableWidget->item(i,1)->text();//表


            //下一个座位
            QString sday = ui->dateTimeEdit->dateTime().toString("yyyy-MM-dd"); //silas


            QString nextseat;
            dia = new QString("select distinct(`seat`.sid),price\
            from `seat`\
            where \
            seat.fid = '")+ fid +"' and \
            seat.sid not in \
            (\
            select `order`.sid\
            from `order`\
            where \
            `order`.fid = '"+fid+"' and\
            date_format(ctime,'%Y-%m-%d') = '"+sday+"');";

            //qDebug()<<dia;

            QSqlQuery query2(db);

            query2.exec(dia);

            if(query2.next()==false) //有没有下一个座位
            {
                rushflag = true;
                continue;
            }

            nextseat = query2.value(0).toString();
            qDebug()<< "下一个座位:"<<nextseat;
            //qDebug()<< count.toInt();




            QString sid = nextseat;//查询
            QString pid = user;
            QString price = ui->tableWidget->item(i,5)->text();//表
            QString ctime = ui->tableWidget->item(i,4)->text();//表


            //查询下一个订单号,为了避免前面已经删除，应该筛选最大值

            QString nextoid;

            //dia = new QString("select max(oid) from `order`;");

            QSqlQuery query(db);
order2:
            qDebug()<<query.exec("select oid from `order`;");

            if(query.next() == false)
            {
                qDebug()<<"订单号无";

                nextoid = "000001";
            }
            else
            {
                qDebug()<<"订单号有";

                query.exec("select max(oid) from `order`;");

                query.next(); //Silas

                nextoid = QString("%1").arg(query.value(0).toInt()+1, 6, 10, QLatin1Char('0')); //query.value(0).toInt();
            }



            //添加订单 注意查询订单号 而且循环保证插入成功
            dia = new QString("INSERT INTO `order`(`oid`, `fid`,`sid`,`pid`, `price`,`ctime`) VALUES('")+ nextoid +\
                     "','" + fid + "','" + sid + "','" +pid + "'," +price + ",'" + ctime.replace("T"," ") + "');";

            //INSERT INTO `order`(`oid`, `fid`,`sid`,`pid`, `price`,`ctime`) VALUES('000001','000001','000001','000003',1400.5,'2019-04-18 14:21:00');
            //qDebug()<<"添加订单A"<<dia;

            qDebug()<<"添加订单A";

            if(query.exec(dia)==false)
            {
                goto order2;
            }

notify2:
            //添加通知单
            //QSqlQuery query(db);

            qDebug()<<query.exec("select nid from notify;");

            bool hav = query.next(); //false

            qDebug()<<"添加通知单";

            if(hav)
            {
                qDebug()<<"通知单有";

                query.exec("select max(nid) from notify;");

                query.next(); //Silas

                QString nextnid = QString("%1").arg(query.value(0).toInt()+1, 6, 10, QLatin1Char('0'));


                if(query.exec(new QString("insert into `notify` values('") + nextnid +"','"+nextoid + "');")==false)
                {
                    goto notify2;
                }
            }
            else
            {
                qDebug()<<"通知单无";

                if(query.exec(new QString("insert into `notify` values('000001','")+nextoid + "');")==false)
                {
                    goto notify2;
                }
                //insert into `notify` values('000001','000001')
            }



billagain2:

            //添加账单

            qDebug()<<"添加账单";

            qDebug()<<query.exec("select bid from bill;");

            hav = query.next(); //false


            if(hav)
            {
                qDebug()<<"账单已有";

                query.exec("select max(bid) from bill;");

                query.next(); //Silas

                QString nextbid = QString("%1").arg(query.value(0).toInt()+1, 6, 10, QLatin1Char('0'));

                dia = new QString("insert into `bill`(`bid`,`oid`,`pid`,`price`,`pay`,`ptime`) values('") +\
                        nextbid +"','"+nextoid+"','"+pid+"',"+price+","+"false"+","+"null" + ");";
                qDebug()<<"账单语句"<<dia;

                if(query.exec(dia)==false)
                {
                    goto billagain2;
                }

                //insert into `bill`(`bid`,`oid`,`pid`,`price`,`pay`,`ptime`) values('000001','000001','000001','4410.5',true,'2019-04-18 14:21:00')
            }
            else
            {
                qDebug()<<"账单没有";

                QString dia = new QString("insert into `bill`(`bid`,`oid`,`pid`,`price`,`pay`,`ptime`) values('000001','") +\
                        nextoid+"','"+pid+"',"+price+","+"false"+","+"null" + ");";
                qDebug()<<"账单语句"<<dia;

                if(query.exec(dia)==false)
                {
                    goto billagain2;
                }
                //qDebug()<<query.exec(new QString("insert into `notify` values('000001','")+nextoid + "');");
                //insert into `notify` values('000001','000001')
            }
        }
        for(int i=0;i<ui->tableWidget_2->rowCount();i++){ //双程回
                if(!ui->tableWidget_2->item(i,0)->checkState())
                    continue;

                qDebug()<<ui->tableWidget_2->item(i,5)->text();

                allpay+=ui->tableWidget_2->item(i,5)->text().toDouble();

//                //查询订单数
//                //QString dia;
//                QString dia("select count(*) from `order`;");
//                QSqlQuery query4(db);
//                query4.exec(dia);
//                query4.next();

//                //QString nextcount(query4.value(0).toInt()+1);
//                qDebug()<<query4.value(0).toInt();

//                QString nextcount = QString("%1").arg(query4.value(0).toInt()+1, 6, 10, QLatin1Char('0'));
//                //nextcount=nextcount.replace("\u","00");
//                qDebug()<<"现在计数"<<nextcount;


                //先构造fid
                QString fid = ui->tableWidget_2->item(i,1)->text();//表


                //下一个座位
                QString sday = ui->dateTimeEdit_2->dateTime().toString("yyyy-MM-dd"); //silas


                QString nextseat;
                dia = new QString("select distinct(`seat`.sid),price\
                from `seat`\
                where \
                seat.fid = '")+ fid +"' and \
                seat.sid not in \
                (\
                select `order`.sid\
                from `order`\
                where \
                `order`.fid = '"+fid+"' and\
                date_format(ctime,'%Y-%m-%d') = '"+sday+"');";

                //qDebug()<<dia;

                QSqlQuery query2(db);

                query2.exec(dia);

                if(query2.next()==false) //有没有下一个座位
                {
                    rushflag = true;
                    continue;
                }

                nextseat = query2.value(0).toString();
                qDebug()<< "下一个座位:"<<nextseat;
                //qDebug()<< count.toInt();




                QString sid = nextseat;//查询
                QString pid = user;
                QString price = ui->tableWidget_2->item(i,5)->text();//表
                QString ctime = ui->tableWidget_2->item(i,4)->text();//表


                //查询下一个订单号,为了避免前面已经删除，应该筛选最大值

                QString nextoid;

                //dia = new QString("select max(oid) from `order`;");

                QSqlQuery query(db);
order3:
                qDebug()<<query.exec("select oid from `order`;");

                if(query.next() == false)
                {
                    qDebug()<<"订单号无";
                    nextoid = "000001";

                }
                else
                {
                    qDebug()<<"订单号有";
                    query.exec("select max(oid) from `order`;");

                    query.next(); //Silas

                    nextoid = QString("%1").arg(query.value(0).toInt()+1, 6, 10, QLatin1Char('0')); //query.value(0).toInt();
                }


                //添加订单 注意查询订单号 而且循环保证插入成功
                dia = new QString("INSERT INTO `order`(`oid`, `fid`,`sid`,`pid`, `price`,`ctime`) VALUES('")+ nextoid +\
                         "','" + fid + "','" + sid + "','" +pid + "'," +price + ",'" + ctime.replace("T"," ") + "');";

                //INSERT INTO `order`(`oid`, `fid`,`sid`,`pid`, `price`,`ctime`) VALUES('000001','000001','000001','000003',1400.5,'2019-04-18 14:21:00');
                //qDebug()<<"添加订单A"<<dia;

                qDebug()<<"添加订单A";

                if(query.exec(dia)==false)
                {
                    goto order3;
                }

notify3:
                //添加通知单
                //QSqlQuery query(db);

                qDebug()<<query.exec("select nid from notify;");

                bool hav = query.next(); //false

                qDebug()<<"添加通知单";

                if(hav)
                {
                    qDebug()<<"通知单有";

                    query.exec("select max(nid) from notify;");

                    query.next(); //Silas

                    QString nextnid = QString("%1").arg(query.value(0).toInt()+1, 6, 10, QLatin1Char('0'));

                    if(query.exec(new QString("insert into `notify` values('") + nextnid +"','"+nextoid+ "');")==false)
                    {
                        goto notify3;
                    }
                }
                else
                {
                    qDebug()<<"通知单无";

                    if(query.exec(new QString("insert into `notify` values('000001','")+nextoid+ "');")==false)
                    {
                        goto notify3;
                    }
                    //insert into `notify` values('000001','000001')
                }




billagain3:

                //添加账单
                qDebug()<<"添加账单";

                qDebug()<<query.exec("select bid from bill;");

                hav = query.next(); //false

                if(hav)
                {
                    qDebug()<<"账单有";

                    query.exec("select max(bid) from bill;");

                    query.next(); //Silas

                    QString nextbid = QString("%1").arg(query.value(0).toInt()+1, 6, 10, QLatin1Char('0'));

                    dia = new QString("insert into `bill`(`bid`,`oid`,`pid`,`price`,`pay`,`ptime`) values('") +\
                            nextbid +"','"+nextoid+"','"+pid+"',"+price+","+"false"+","+"null" + ");";
                    qDebug()<<"账单语句"<<dia;

                    if(query.exec(dia)==false)
                    {
                        goto billagain3;
                    }

                    //insert into `bill`(`bid`,`oid`,`pid`,`price`,`pay`,`ptime`) values('000001','000001','000001','4410.5',true,'2019-04-18 14:21:00')
                }
                else
                {
                    qDebug()<<"账单无";

                    dia = new QString("insert into `bill`(`bid`,`oid`,`pid`,`price`,`pay`,`ptime`) values('000001','") +\
                            nextoid+"','"+pid+"',"+price+","+"false"+","+"null" + ");";
                    qDebug()<<"账单语句"<<dia;

                    if(query.exec(dia)==false)
                    {
                        goto billagain3;
                    }
                    //qDebug()<<query.exec(new QString("insert into `notify` values('000001','")+nextoid + "');");
                    //insert into `notify` values('000001','000001')
                }
         }//endfor
        qDebug()<<allpay;
    }

    if(allpay == 0)
    {
        QMessageBox::critical(this ,
        "错误" , "请先勾选你要购买的航班！",
        QMessageBox::Ok, 0, 0);
        return;
    }
    //提示成功
//    QMessageBox box(QMessageBox::Information,"消息","订票成功！");
//    box.setStandardButtons (QMessageBox::Ok);
//    box.setButtonText (QMessageBox::Ok,QString("确 定"));
//    box.exec ();




    //支付提示
    bool wannapay = false; //是则转入订单中心

    //Silas取票标记
    QMessageBox mb(QMessageBox::Information, "提示", new QString("订票成功！是否转到订单中心支付？") + ((rushflag == true)?QString("部分可能抢票失败！"):QString("抢票全部成功！")), QMessageBox::Yes|QMessageBox::No);
    mb.setButtonText( QMessageBox::Yes, "是" );
    mb.setButtonText( QMessageBox::No, "否" );
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


//    QMessageBox mb( "提示",
//            "订票成功！是否支付？",
//            QMessageBox::Information,
//            QMessageBox::Yes | QMessageBox::Default,
//            QMessageBox::No  | QMessageBox::Escape );
//            //QMessageBox::Cancel | QMessageBox::Escape );
//    mb.setButtonText( QMessageBox::Yes, "是" );
//    mb.setButtonText( QMessageBox::No, "否" );
//    //mb.setButtonText( QMessageBox::Cancel, "取消" );
//    switch( mb.exec() )
//    {
//        case QMessageBox::Yes:
//            // 保存并且退出
//           //printf("save");
////            QMessageBox box(QMessageBox::Information,"消息","订票成功！是否转到订单中心支付？");
////            box.setStandardButtons (QMessageBox::Ok);
////            box.setButtonText (QMessageBox::Ok,QString("确 定"));
////            box.exec ();
//            wannapay = true;



//            qDebug()<<"sav";
//            break;
//        case QMessageBox::No:
//            // 不保存退出

//           qDebug()<<"Unsav";
//            break;
////        case QMessageBox::Cancel:
////            // 不保存并且不退出
////           qDebug()<<"cancel";

////            break;
//    }


    if(wannapay)
    {
        up2 = new UserPan();
        up2->user=user;
        this->hide();
        up2->showlist();
        up2->show();
        up2->exec();

        //重新连接
        if (QSqlDatabase::contains("mysql")) {
            db = QSqlDatabase::database("mysql");
            qDebug()<<"mysql---";
        } else {
            db = QSqlDatabase::addDatabase("QMYSQL", "mysql");
            qDebug()<<"QMYSQL---mysql";
        }


        db.setHostName(     HostName + "");
        db.setPort(           Port.toInt());
        db.setDatabaseName( DatabaseName + "");
        db.setUserName(      UserName + "");
        db.setPassword(      Password + "");
              ok = db.open();
              if(ok)  qDebug()<<"OK";
              else qDebug()<<"False";



        qDebug()<<"return now!!";

        this->show();
    }


}

void ChoosePan::on_pushButton_8_clicked()
{
//    QString connection;
//    connection=db.connectionName(); //->connectionName();
//    delete(&db);
//    QSqlDatabase::removeDatabase(connection);

    ui->pushButton_8->setDisabled(true);
    up2 = new UserPan();
    up2->user=user;
    this->hide();
    up2->showlist();
    up2->show();
    up2->exec();

    ui->pushButton_8->setDisabled(false);

    //重新连接
    if (QSqlDatabase::contains("mysql")) {
        db = QSqlDatabase::database("mysql");
        qDebug()<<"mysql---";
    } else {
        db = QSqlDatabase::addDatabase("QMYSQL", "mysql");
        qDebug()<<"QMYSQL---mysql";
    }

    db.setHostName(     HostName + "");
    db.setPort(           Port.toInt());
    db.setDatabaseName( DatabaseName + "");
    db.setUserName(      UserName + "");
    db.setPassword(      Password + "");
          ok = db.open();
          if(ok)  qDebug()<<"OK";
          else qDebug()<<"False";



    qDebug()<<"return now!!";
    this->show();

}

void ChoosePan::on_pushButton_7_clicked() //查询指定航班的预定情况（哪些空位）、计算航班的满座率（%）。
{
    if(ui->lineEdit_6->text().trimmed().isEmpty())
    {
        return;
    }

    double allseat = 1;
    double havseat;

    ui->textBrowser->setText("");
    //ui->textBrowser->append();

    QString hb = ui->lineEdit_6->text();

    QString sday = ui->dateEdit->dateTime().toString("yyyy-MM-dd");

    QString dia(new QString("select count(distinct(`seat`.sid))\
                            from `seat`\
                            where \
                            seat.fid = '")+ hb + "' and "\
            "seat.sid in \
            (\
            select `order`.sid\
            from `order`\
            where \
            `order`.fid = '"+ hb + "' and\
            date_format(ctime,'%Y-%m-%d') = '"+ sday +"');"   );


    qDebug()<<"满座"<<dia;

    QSqlQuery query5(db);
    query5.exec(dia);
    query5.next();
    havseat = query5.value(0).toDouble();


    //座位数
    dia = new QString("select count(distinct(`seat`.sid))\
                      from `seat`\
                      where seat.fid = '")+ hb +"' ;";
            QSqlQuery query6(db);
            query6.exec(dia);
            query6.next();
            allseat = query6.value(0).toDouble();

    qDebug()<<"座位数"<<dia;

    if(allseat == 0)
    {
        ui->textBrowser->insertPlainText(hb);
        ui->textBrowser->insertPlainText("航班没有安排\r\n\r\n");
        return;
    }

    double rate = havseat/allseat;


    ui->textBrowser->insertPlainText("航班"); //append("航班");
    ui->textBrowser->insertPlainText(hb);
    ui->textBrowser->insertPlainText("的满座率为：");
    ui->textBrowser->insertPlainText(QString::number(rate));

    //空位展示
    dia = new QString("select distinct(`seat`.sid)\
                                from `seat`\
                                where \
                                seat.fid = '")+ hb + "' and "\
                "seat.sid not in \
                (\
                select `order`.sid\
                from `order`\
                where \
                `order`.fid = '"+ hb + "' and\
                date_format(ctime,'%Y-%m-%d') = '"+ sday +"');";

            qDebug()<<"空位展示"<<dia;


            ui->textBrowser->insertPlainText("\r\n现在空位有：");
            QSqlQuery query7(db);
            query7.exec(dia);
            while(query7.next())
            {
                ui->textBrowser->insertPlainText(query7.value(0).toString());
                ui->textBrowser->insertPlainText(" ");
            }
            ui->textBrowser->insertPlainText("\r\n\r\n");

}

void ChoosePan::on_pushButton_9_clicked()//查询每个/所有航班的预定情况、计算航班的满座率。
{
    ui->textBrowser->clear();
    QString dia = "select distinct(fid) from flight;";
    QSqlQuery query8(db);
    query8.exec(dia);

    while(query8.next())
    {
        QString hb = query8.value(0).toString();


        //复用代码
        double allseat = 1;
        double havseat;

        //ui->textBrowser->append();

        QString sday = ui->dateEdit->dateTime().toString("yyyy-MM-dd");

        QString dia(new QString("select count(distinct(`seat`.sid))\
                                from `seat`\
                                where \
                                seat.fid = '")+ hb + "' and "\
                "seat.sid in \
                (\
                select `order`.sid\
                from `order`\
                where \
                `order`.fid = '"+ hb + "' and\
                date_format(ctime,'%Y-%m-%d') = '"+ sday +"');"   );


        qDebug()<<"满座"<<dia;

        QSqlQuery query5(db);
        query5.exec(dia);
        query5.next();
        havseat = query5.value(0).toDouble();


        //座位数
        dia = new QString("select count(distinct(`seat`.sid))\
                          from `seat`\
                          where seat.fid = '")+ hb +"' ;";
                QSqlQuery query6(db);
                query6.exec(dia);
                query6.next();
                allseat = query6.value(0).toDouble();

        qDebug()<<"座位数"<<dia;

        if(allseat == 0)
        {
            continue;
        }

        double rate = havseat/allseat;


        ui->textBrowser->insertPlainText("航班"); //append("航班");
        ui->textBrowser->insertPlainText(hb);
        ui->textBrowser->insertPlainText("的满座率为：");
        ui->textBrowser->insertPlainText(QString::number(rate));

        //空位展示
        dia = new QString("select distinct(`seat`.sid)\
                                    from `seat`\
                                    where \
                                    seat.fid = '")+ hb + "' and "\
                    "seat.sid not in \
                    (\
                    select `order`.sid\
                    from `order`\
                    where \
                    `order`.fid = '"+ hb + "' and\
                    date_format(ctime,'%Y-%m-%d') = '"+ sday +"');";

                qDebug()<<"空位展示"<<dia;


                ui->textBrowser->insertPlainText("\r\n现在空位有：");
                QSqlQuery query7(db);
                query7.exec(dia);
                while(query7.next())
                {
                    ui->textBrowser->insertPlainText(query7.value(0).toString());
                    ui->textBrowser->insertPlainText(" ");
                }
                ui->textBrowser->insertPlainText("\r\n\r\n");
    }

}

void ChoosePan::on_action_triggered()
{
    int goexit = 0;

        QMessageBox mb( "提示",
                "确定退出？",
                QMessageBox::Information,
                QMessageBox::Yes | QMessageBox::Default,
                QMessageBox::No ,
                QMessageBox::Cancel | QMessageBox::Escape );
        mb.setButtonText( QMessageBox::Yes, "退出" );
        mb.setButtonText( QMessageBox::No, "不退出" );
        mb.setButtonText( QMessageBox::Cancel, "取消" );
        switch( mb.exec() )
        {
            case QMessageBox::Yes:
                goexit = 1;
                break;
            case QMessageBox::No:

                break;
        case QMessageBox::Cancel:

            break;
        }
        if(!goexit)
            return;
        QApplication::exit();

}

void ChoosePan::on_action_2_triggered()
{
    QMessageBox box(QMessageBox::Information,"使用方法",
                    "配置数据库配置文件conf.ini请勿使用中文\n"
                    "配置完之后需要重启程序\n"
                        "全GUI操作界面，采用Qt 5.9.2开发，支持64位和32位系统\n"
                        "如果需要深入了解、分支维护请查阅开发文档");
        box.exec ();
}

void ChoosePan::on_action_3_triggered()
{
    QMessageBox box(QMessageBox::Information,"关于","开源工具@Silas");
    box.exec ();
}



void ChoosePan::on_action_5_triggered()
{
    thread->start();
}
