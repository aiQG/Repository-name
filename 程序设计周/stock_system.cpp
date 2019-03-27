#include "stock_system.h"
#include "ui_stock_system.h"
#include "mypaint.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QTableWidget>
#include <QSqlDriver>
#include <QTimer>
#include <iostream>
#include "out_stock.h"
#include "warning_line.h"
#include <QMessageBox>
#include <QMenu>
using namespace std;
#include <QApplication>
Stock_System::Stock_System(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Stock_System)
{
    //数据库和表的建立及打开
    db=open_db(1);
    query=create_query();

    //建立表格，初始化并设置格式
    int count=1000;
    ui->setupUi(this);
    ui->label_d->show();
    ui->table->setRowCount(count);
    ui->table->setColumnCount(4);
    ui->table->setHorizontalHeaderLabels(QStringList()<<"编号"<<"名称"<<"类别"<<"数量");
    ui->table->verticalHeader()->hide();                                                    //隐藏左边序号
    ui->table->horizontalHeader()->setStretchLastSection(true);                             //拉长最后一列
    ui->table->setStyleSheet(QString("QTableWidget QHeaderView::section{background:#2a9ee4;font-weight:bold; border:none; height:35px; color:white;}"));
    ui->table->setAlternatingRowColors(true);                                               //开启间隔行颜色



    //设置字体黑色
    //ui->table->setStyleSheet("color:black");
    ui->identifer->setStyleSheet("color:black");
    ui->category->setStyleSheet("color:black");
    ui->goodsname->setStyleSheet("color:black");
    ui->pushButton_3->setStyleSheet("color:black");
    ui->pushButton_4->setStyleSheet("color:black");
    ui->pushButton_5->setStyleSheet("color:black");
    ui->input->setStyleSheet("color:black");
    ui->out->setStyleSheet("color:black");
    ui->label->setStyleSheet("color:black");
    ui->label_2->setStyleSheet("color:black");
    ui->label_3->setStyleSheet("color:black");
    ui->label_4->setStyleSheet("color:black");
    ui->label_d->setStyleSheet("color:black");
    ui->label_5->setStyleSheet("color:black");
    ui->pushButton_6->setStyleSheet("color:black");
    this->setStyleSheet("color:black");

    //设置透明
    this->setWindowOpacity(1); //窗口整体透明度，0-1 从全透明到不透明
    this->setWindowFlags(Qt::FramelessWindowHint); //设置无边框风格
    this->setAttribute(Qt::WA_TranslucentBackground); //设置背景透明，允许鼠标穿透
    //插入图片
    ui->centralWidget->setStyleSheet("#centralWidget{background-image: url(:/image/book.png);}");


    //设定窗口大小
    setFixedSize(1187,850);




    //初始化表格
    warnLine="20";
    init_db();


    //建立主页中三个按钮的信号连接
    connect(ui->pushButton_5,SIGNAL(clicked(bool)),this,SLOT(on_search()));
    connect(ui->pushButton_3,SIGNAL(clicked(bool)),this,SLOT(on_home()));
    connect(ui->out,SIGNAL(clicked(bool)),this,SLOT(on_out_clicked()));

    //进货弹出框
    clickImport =new Input(this);
    connect(clickImport,SIGNAL(sendvarydata_1()),this,SLOT(receive_new_input()));
    connect(clickImport,SIGNAL(sendvarydata_2()),this,SLOT(receive_old_input()));

    //出货弹出框
    clickOut = new Out_stock(this);
    connect(clickOut,SIGNAL(out_vary_data()),this,SLOT(receive_output()));

}

Stock_System::~Stock_System()
{
    db.close();
    delete ui;
}

//创建或打开数据库
QSqlDatabase Stock_System::open_db(int n)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");         //创建本地数据库
    db.setDatabaseName("supermarket");
    if (!db.open())                                                 //如果打不开，则直接退出
    {
        qDebug()<<QObject::tr("无法打开");
        if (n<=5)                                                   //如果打不开则重试五次
            open_db(n+1);
        else
            exit(1);
    }
    return db;
}

//创建查询指针
QSqlQuery Stock_System::create_query()
{
    QSqlQuery query;
    bool success=query.exec("create table goods (id int pirmary key,name varchar,category varchar,number long)");
    if (success)                                                        //如果已经有了，则创建失败
    {
            qDebug()<<QObject::tr("创建成功");
    }
    else
    {
            QSqlError lastError=query.lastError();
            qDebug()<<lastError.driverText()<<QString(QObject::tr("创建失败"));
            query.exec("use table goods");
    }
    return query;
}

//初始化数据库
void Stock_System::init_db()
{
    ui->table->clear();
    ui->table->setHorizontalHeaderLabels(QStringList()<<"编号"<<"名称"<<"类别"<<"数量");

    QString parme="select * from goods";
    int i=0;
    if (!query.exec(parme))
    {
        qDebug()<<query.lastError();
    }
    else
    {
        while(query.next())                                         //循环将数据库中的文件显示在表格中
        {
           QString id=query.value(0).toString();
           QString name=query.value(1).toString();
           QString category=query.value(2).toString();
           QString number=query.value(3).toString();
           ui->table->setItem(i,0,new QTableWidgetItem(id));
           ui->table->setItem(i,1,new QTableWidgetItem(name));
           ui->table->setItem(i,2,new QTableWidgetItem(category));
           ui->table->setItem(i++,3,new QTableWidgetItem(number));
        }
    }
    QString dynamiclabel="";
    parme="select name from goods where number<"+warnLine;
    query.exec(parme);
    while(query.next())
    {
        QString warnName=query.value(0).toString();
        dynamiclabel+=warnName+"     ";
    }

    ui->label_d->changetext(dynamiclabel);
    return ;
}

//查询按钮的槽函数
void Stock_System::on_search()                            //查询按钮
{
    ui->table->clear();
    ui->table->setHorizontalHeaderLabels(QStringList()<<"编号"<<"名称"<<"类别"<<"数量");    //此处无需控制输入，因为如果输入错误，则没有相应物品
    QString identifer=ui->identifer->text();
    QString goodsname=ui->goodsname->text();
    QString category=ui->category->text();
    QString stl="'";
    if (identifer!="")                                                      //以编号为第一搜索
    {
        QString parme="select * from goods where id="+identifer;
        int i=0;
        if (!query.exec(parme))
        {
            qDebug()<<query.lastError();
        }
        else
        {
            while(query.next())
            {
               QString id=query.value(0).toString();
               QString name=query.value(1).toString();
               QString category=query.value(2).toString();
               QString number=query.value(3).toString();
               ui->table->setItem(i,0,new QTableWidgetItem(id));
               ui->table->setItem(i,1,new QTableWidgetItem(name));
               ui->table->setItem(i,2,new QTableWidgetItem(category));
               ui->table->setItem(i++,3,new QTableWidgetItem(number));
            }
        }
    }
    else
    {
        if (goodsname!="")                                  //物品名为第二搜索
        {
            QString parme="select * from goods where name="+stl+goodsname+stl;
         //   qDebug()<<parme;
            int i=0;
            if (!query.exec(parme))
            {
                qDebug()<<query.lastError();
            }
            else
            {
                while(query.next())
                {
                   QString id=query.value(0).toString();
                   QString name=query.value(1).toString();
                   QString category=query.value(2).toString();
                   QString number=query.value(3).toString();
                   ui->table->setItem(i,0,new QTableWidgetItem(id));
                   ui->table->setItem(i,1,new QTableWidgetItem(name));
                   ui->table->setItem(i,2,new QTableWidgetItem(category));
                   ui->table->setItem(i++,3,new QTableWidgetItem(number));
                }
            }
         }
        else
        {
            if (category!="")                                   //类型为第三搜索
            {
                QString parme="select * from goods where category="+stl+category+stl;
                int i=0;
                if (!query.exec(parme))
                {
                    qDebug()<<query.lastError();
                }
                else
                {
                    while(query.next())
                    {
                       QString id=query.value(0).toString();
                       QString name=query.value(1).toString();
                       QString category=query.value(2).toString();
                       QString number=query.value(3).toString();
                       ui->table->setItem(i,0,new QTableWidgetItem(id));
                       ui->table->setItem(i,1,new QTableWidgetItem(name));
                       ui->table->setItem(i,2,new QTableWidgetItem(category));
                       ui->table->setItem(i++,3,new QTableWidgetItem(number));
                    }
                }
            }
            else                                                            //如果什么都不输入直接查询，则应弹出提示框
            {
                ui->warning->show();
                ui->warning->setText("请输入查询信息！！！");
                ui->warning->setStyleSheet("color:red;");
                init_db();
                QTimer::singleShot(3000,this,SLOT(hide_warning()));
            }
        }
    }
    ui->goodsname->clear();
    ui->identifer->clear();
    ui->category->clear();
}

//主页键即刷新左方表格
void Stock_System::on_home()
{
    init_db();
}

//隐藏警告
void Stock_System::hide_warning()
{
    ui->warning->hide();
}

//进货按钮
void Stock_System::on_input_clicked()
{
        clickImport->show();            //使进货框显现
        clickImport->able();            //是按钮有效
        clickImport->clear();           //清空
        clickImport->hidewarning();     //隐藏新款的提示框
        clickImport->hidewarning_2();   //隐藏旧款的提示框
}

int Stock_System::isnumber(QString src)
{
    QByteArray ba = src.toLatin1();//QString 转换为 char*
     const char *s = ba.data();

    while(*s && *s>='0' && *s<='9') s++;

    if (*s)
    { //不是纯数字
        return -1;
    }
    else
    { //纯数字
        return 0;
    }
}

//接受新品
void Stock_System::receive_new_input()
{
    QString str="'";
    QString id=clickImport->get_id(1);
    QString name=clickImport->get_name(1);
    QString category=clickImport->get_category();
    QString number=clickImport->get_number(1);
    int isnum=isnumber(number);                                         //判断数量是否为纯正整数数字串
    if (isnum==0 && number.toLong()>0)
    {
        if (id=="" || name=="" || category=="" || number=="")           //输入不完整的提醒
        {
            clickImport->warning("请输入完整信息");
        }
        else
        {
           QString str="'";
           QString prame="select * from goods where name="+str+name+str;
           query.exec(prame);
           query.next();
           if (query.isValid())
           {
               clickImport->clear();
               QMessageBox message(QMessageBox::Warning,"Information","此物品已存在，请点击老款进货",QMessageBox::Ok,NULL);
               if (message.exec()==QMessageBox::Yes)
               {
                   clickImport->clear();
                   message.close();
               }
           }
           else
           {
               prame="select * from goods where id="+id;
               query.exec(prame);
               query.next();
               if (query.isValid())
               {
                   clickImport->clear();
                   QMessageBox message(QMessageBox::Warning,"Information","此物品已存在，请点击老款进货",QMessageBox::Ok,NULL);
                   if (message.exec()==QMessageBox::Ok)
                   {
                       clickImport->clear();
                       message.close();
                   }
               }
               else
               {
                   QString parme="insert into goods values("+id+","+str+name+str+","+str+category+str+","+number+")";
                   query.exec(parme);

                   //保存到记录
                   QDate ctime = QDate::currentDate();
                   QString Ctime = ctime.toString("yyyy-MM-dd"); //设置显示格式
                   //保存到文件
                   QFile F("Input.txt");
                   F.open(QIODevice::WriteOnly|QIODevice::Append);
                   QTextStream f(&F);
                   f<<(QString)"入库,"<<Ctime<<","<<id<<","<<name<<","<<number<<endl;
                   F.close();



                   clickImport->add_success();
                   init_db();
               }
           }
        }
    }
    else
        clickImport->warning("数量必须为正整数数字！");
}


void Stock_System::receive_old_input()
{
    QString  val=clickImport->get_number(2);
    int isnum=isnumber(val);
    if (isnum==0 && val.toLong()>0)                             //判断正整数
    {
        long number=val.toLong();
        int current_status=clickImport->getstatus();
        if (current_status==0)
        {
          //依据编号进货
            QString id=clickImport->get_id(2);
            if (number==0 || id=="")
            {
                clickImport->warning_3();
            }
            else
            {
                QString parme="select * from goods where id="+id;
                if (!query.exec(parme))
                {
                    qDebug()<<query.lastError();

                }
                else
                {
                    query.next();
                    if (query.isValid())                //如果输入的商品不存在，则查询错误，需要提示
                    {
                        long long currentnumber=query.value(3).toLongLong();
                        long changednumber=currentnumber+number;
                        QString num=QString::number(changednumber);
                        parme="update goods set number="+num+" where id="+id;
                        if (!query.exec(parme))
                        {
                            qDebug()<<query.lastError();
                        }
                        else
                        {


                            //搜索此条
                            QString parme="select * from goods where id="+id;
                            query.exec(parme);
                            //只有一个id 只能搜到一个条目
                            query.next();
                            QString getId=query.value(0).toString();
                            QString getName=query.value(1).toString();
                            QString getCategory=query.value(2).toString();
                            //QString getNumber=num;//增加的数量
                            QDate ctime = QDate::currentDate();
                            QString Ctime = ctime.toString("yyyy-MM-dd"); //设置显示格式
                            //保存到文件
                            QFile F("Input.txt");
                            F.open(QIODevice::WriteOnly|QIODevice::Append);
                            QTextStream f(&F);
                            f<<(QString)"入库,"<<Ctime<<","<<id<<","<<getName<<","<<number<<endl;
                            F.close();



                            clickImport->changesuccess();
                            init_db();
                        }
                    }
                    else
                    {
                            QMessageBox message(QMessageBox::Warning,"Information","此物品不存在，请切换到新品栏中输入完整商品信息",QMessageBox::Ok,NULL);
                            if (message.exec()==QMessageBox::Ok)
                            {
                                clickImport->clear();
                                message.close();
                            }
                    }
                }
            }
        }
        else
        {
            //依据名称进货
            QString str="'";
            QString name=clickImport->get_name(2);
            if (name=="" || number==0)
                clickImport->warning_3();
            else
            {
                QString parme="select * from goods where name="+str+name+str;
                if (!query.exec(parme))
                {
                    qDebug()<<query.lastError();
                }
                else
                {
                    query.next();
                    if (query.isValid())                    //判断名称的有效性
                    {
                        long currentnumber=query.value(3).toLongLong();
                        long changednumber=currentnumber+number;
                        QString num=QString::number(changednumber);
                        parme="update goods set number="+num+" where name="+str+name+str;
                        if (!query.exec(parme))
                        {
                            qDebug()<<query.lastError();
                        }
                        else
                        {


                            //搜索此条
                            QString parme="select * from goods where name="+str+name+str;
                            query.exec(parme);
                            //只有一个id 只能搜到一个条目
                            query.next();
                            QString getId=query.value(0).toString();
                            QString getName=query.value(1).toString();
                            QString getCategory=query.value(2).toString();
                            QDate ctime = QDate::currentDate();
                            QString Ctime = ctime.toString("yyyy-MM-dd"); //设置显示格式
                            //保存到文件
                            QFile F("Input.txt");
                            F.open(QIODevice::WriteOnly|QIODevice::Append);
                            QTextStream f(&F);
                            f<<(QString)"入库,"<<Ctime<<","<<getId<<","<<getName<<","<<number<<endl;
                            F.close();



                            clickImport->changesuccess();
                            init_db();
                        }
                    }
                    else
                    {
                        clickImport->clear();
                        QMessageBox message(QMessageBox::Warning,"Information","此物品不存在，请切换到新品栏中输入完整商品信息",QMessageBox::Ok,NULL);
                        if (message.exec()==QMessageBox::Yes)
                        {
                            message.close();
                        }
                    }
                }

            }
        }
    }
     else
     {
         QMessageBox message(QMessageBox::Warning,"Information","数字栏只能输入0-9！",QMessageBox::Ok,NULL);
         if (message.exec()==QMessageBox::Ok)
         {
             clickImport->clear();
             message.close();
         }
     }
}

void Stock_System::receive_output()                 //出库数据改变
{
    QString  val=clickOut->get_number();
    int current_status=clickOut->getstatus();
    if  (isnumber(val)==0 && val.toLong()>0)
    {
        long number=val.toLong();
        if (current_status==0)
        {
              //依据编号出库
                QString id=clickOut->get_id();
                if (number==0 || id=="")
                {
                    clickOut->out_warning();
                }
                else
                {
                    QString parme="select * from goods where id="+id;
                    if (!query.exec(parme))
                    {
                        qDebug()<<query.lastError();
                    }
                    else
                    {
                        query.next();
                        if (query.isValid())
                        {
                            long long currentnumber=query.value(3).toLongLong();
                            if (currentnumber>=number)                      //如果库存余量不足也需提醒
                            {
                                long changednumber=currentnumber-number;
                                QString num=QString::number(changednumber);
                                parme="update goods set number="+num+" where id="+id;
                                if (!query.exec(parme))
                                {
                                    cout<<"执行修改错误";
                                    qDebug()<<query.lastError();
                                }
                                else
                                {


                                    //搜索此条
                                    QString parme="select * from goods where id="+id;
                                    query.exec(parme);
                                    //只有一个id 只能搜到一个条目
                                    query.next();
                                    QString getId=query.value(0).toString();
                                    QString getName=query.value(1).toString();
                                    QString getCategory=query.value(2).toString();
                                    //QString getNumber=num;//增加的数量
                                    QDate ctime = QDate::currentDate();
                                    QString Ctime = ctime.toString("yyyy-MM-dd"); //设置显示格式
                                    //保存到文件
                                    QFile F("Output.txt");
                                    F.open(QIODevice::WriteOnly|QIODevice::Append);
                                    QTextStream f(&F);
                                    f<<(QString)"出库,"<<Ctime<<","<<id<<","<<getName<<","<<number<<endl;
                                    F.close();



                                    clickOut->out_success();
                                    init_db();
                                }
                            }
                            else
                            {
                                QMessageBox message(QMessageBox::Warning,"Information","余量不足！请重新选择出库量",QMessageBox::Ok,NULL);
                                if (message.exec()==QMessageBox::Ok)
                                {
                                    clickOut->clear();
                                    message.close();
                                }
                            }
                        }
                        else
                        {
                            QMessageBox message(QMessageBox::Warning,"Information","商品不存在，请重新确认",QMessageBox::Ok,NULL);
                            if (message.exec()==QMessageBox::Ok)
                            {
                                clickOut->clear();
                                message.close();
                            }
                        }
                    }
                }
        }
        else
        {
            //名称
                QString str="'";
                QString name=clickOut->get_name();
                if (name=="" || number==0)
                    clickOut->out_warning();
                else
                {
                    QString parme="select * from goods where name="+str+name+str;
                    if (!query.exec(parme))
                    {
                        qDebug()<<query.lastError();
                    }
                    else
                    {
                        query.next();
                        if (query.isValid())
                        {
                            long currentnumber=query.value(3).toLongLong();
                            if (currentnumber>=number)
                            {
                                long changednumber=currentnumber-number;
                                QString num=QString::number(changednumber);
                                parme="update goods set number="+num+" where name="+str+name+str;
                                if (!query.exec(parme))
                                {
                                    qDebug()<<query.lastError();
                                }
                                else
                                {


                                    //搜索此条
                                    QString parme="select * from goods where name="+str+name+str;
                                    query.exec(parme);
                                    //只有一个id 只能搜到一个条目
                                    query.next();
                                    QString getId=query.value(0).toString();
                                    QString getName=query.value(1).toString();
                                    QString getCategory=query.value(2).toString();
                                    QDate ctime = QDate::currentDate();
                                    QString Ctime = ctime.toString("yyyy-MM-dd"); //设置显示格式
                                    //保存到文件
                                    QFile F("Output.txt");
                                    F.open(QIODevice::WriteOnly|QIODevice::Append);
                                    QTextStream f(&F);
                                    f<<(QString)"出库,"<<Ctime<<","<<getId<<","<<getName<<","<<number<<endl;
                                    F.close();



                                    clickOut->out_success();
                                    init_db();
                                }
                            }
                            else
                            {
                                QMessageBox message(QMessageBox::Warning,"Information","余量不足！请重新选择出库量",QMessageBox::Ok,NULL);
                                if (message.exec()==QMessageBox::Ok)
                                {
                                    clickOut->clear();
                                    message.close();
                                }
                            }
                        }
                        else
                        {
                            QMessageBox message(QMessageBox::Warning,"Information","商品不存在，请重新确认",QMessageBox::Ok,NULL);
                            if (message.exec()==QMessageBox::Ok)
                            {
                                clickOut->clear();
                                message.close();
                            }
                        }
                    }

                }
        }
    }
    else
    {
        QMessageBox message(QMessageBox::Warning,"Information","数字栏只能输入0-9！",QMessageBox::Ok,NULL);
        if (message.exec()==QMessageBox::Ok)
        {
            clickOut->clear();
            message.close();
        }
    }
}





void Stock_System::on_out_clicked()
{
    clickOut->show();
    clickOut->able();            //是按钮有效
    clickOut->clear();           //清空
    clickOut->warning_hide();
}

/*
void Stock_System::on_actionformat_changed()
{
    QString parme="delete from goods";
    query.exec(parme);
    init_db();
}
*/
/*
void Stock_System::on_actionwarning_line_changed()
{
    warn=new warning_line();
    warn->show();
    connect(warn,SIGNAL(send_warning_line()),this,SLOT(receive_warning_line()));
}
*/
void Stock_System::receive_warning_line()
{
    QString temp=warn->getnumber();
    if (!isnumber(temp))
    {
        warnLine=temp;
        init_db();
        warn->close();
    }
    else
    {
        QMessageBox message(QMessageBox::Warning,"Information","数字栏只能输入数字！",QMessageBox::Ok,NULL);
        if (message.exec()==QMessageBox::Ok)
        {
            clickOut->clear();
            message.close();
        }
    }

}

void Stock_System::on_pushButton_4_clicked()
{
    DZ.inputJournal();//更新
    DZ.show();
}

void Stock_System::on_pushButton_6_clicked()
{
    exit(1);
}


void Stock_System::on_pushButton_8_clicked()
{
    warn=new warning_line();
    warn->show();
    connect(warn,SIGNAL(send_warning_line()),this,SLOT(receive_warning_line()));
}

void Stock_System::on_pushButton_7_clicked()
{
    QString parme="delete from goods";
    query.exec(parme);
    init_db();
}
