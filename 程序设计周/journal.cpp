#include "journal.h"
#include "ui_Journal.h"
#include "change.h"
#include "ui_change.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QTextCodec>



Journal::Journal(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Journal)
{
    ui->setupUi(this);
    ui->tableWidget->setRowCount(100000);
    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"类别"<<"时间"<<"编号"<<"名称"<<"数量");
    ui->tableWidget->verticalHeader()->hide();                            //隐藏左边序号
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);     //拉长最后一列
    ui->tableWidget->setItem(0,0,new QTableWidgetItem("item1"));
    ui->tableWidget->setStyleSheet(QString("QTableWidget QHeaderView::section{background:#2a9ee4;font-weight:bold; border:none; height:35px; color:white;}""QTableWidget{gridline-color:#2aaee4; color:#888; border:none;}"));
    ui->tableWidget->setAlternatingRowColors(true);  //开启间隔行颜色
    //字体黑色
    ui->tableWidget->setStyleSheet("color:black");
    ui->JournalLabel->setStyleSheet("color:black");
    ui->tableWidget->setStyleSheet("color:black");
    ui->OptionLabel->setStyleSheet("color:black");
    ui->TypeLabel->setStyleSheet("color:black");
    ui->InradioButton->setStyleSheet("color:black");
    ui->OutradioButton->setStyleSheet("color:black");
    ui->AllradioButton->setStyleSheet("color:black");
    ui->pushButton_8->setStyleSheet("color:black");
    ui->pushButton_7->setStyleSheet("color:black");
    this->setStyleSheet("color:black");


    //设置透明
    this->setWindowOpacity(1); //窗口整体透明度，0-1 从全透明到不透明
    this->setWindowFlags(Qt::FramelessWindowHint); //设置无边框风格
    this->setAttribute(Qt::WA_TranslucentBackground); //设置背景透明，允许鼠标穿透

    //插入图片
    ui->widget_2->setStyleSheet("#widget_2{background-image: url(:/image/J.png);}");



    //设定窗口大小
    setFixedSize(1245,707);




    //显示修改时间框
    t =new Change(this);
    connect(this,SIGNAL(TIMshow()),t,SLOT(receiveTime())); //关联信号和槽
    //connect(t,SIGNAL(showjournal()),this,SLOT(receiveJournal()));
    this->inputJournal();//初始化




}

Journal::~Journal()
{
    delete ui;
}
//int Journal::count=0;
void Journal::inputJournal()  //文件写入日志
{
    count=0;
    QFile file1("Input.txt");
    //判断文件是否存在
    if(file1.exists())
    {
        qDebug()<<QObject::tr("入库文件已经存在！");
    }else
    {
        //提示成功
        qDebug()<<QObject::tr("入库文件创建成功！");
    }
    if(file1.open(QIODevice::ReadWrite | QIODevice::Text ))
   {
        QString journaldate_1;
        do
        {
            journaldate_1=QString::fromLocal8Bit( file1.readLine().trimmed());
            QString str =journaldate_1.section(',',0,0);
            QString Ctime = journaldate_1.section(',', 1, 1);
            QString id = journaldate_1.section(',', 2, 2);
            QString name = journaldate_1.section(',', 3, 3);
            QString number = journaldate_1.section(',', 4, 4);

            ui->tableWidget->setItem(count,0,new QTableWidgetItem(str));
            ui->tableWidget->setItem(count,1,new QTableWidgetItem(Ctime));
            ui->tableWidget->setItem(count,2,new QTableWidgetItem(id));
            ui->tableWidget->setItem(count,3,new QTableWidgetItem(name));
            ui->tableWidget->setItem(count++,4,new QTableWidgetItem(number));
        }while (!file1.atEnd());
    }
    else {
        qDebug()<<QObject::tr("打开失败");
    }
    file1.close();

    QFile file2("Output.txt");
    //判断文件是否存在
    if(file2.exists())
    {
        qDebug()<<QObject::tr("出库文件已经存在！");
    }else
    {
        //提示成功
        qDebug()<<QObject::tr("出库文件创建成功！");
    }
    if (file2.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QString journaldate_2;
        do
        {
            journaldate_2=QString::fromLocal8Bit(file2.readLine().trimmed());
            QString str =journaldate_2.section(',', 0, 0);
            QString Ctime = journaldate_2.section(',', 1, 1);
            QString id = journaldate_2.section(',', 2, 2);
            QString name = journaldate_2.section(',', 3, 3);
            QString number = journaldate_2.section(',', 4, 4);

            ui->tableWidget->setItem(count,0,new QTableWidgetItem(str));
            ui->tableWidget->setItem(count,1,new QTableWidgetItem(Ctime));
            ui->tableWidget->setItem(count,2,new QTableWidgetItem(id));
            ui->tableWidget->setItem(count,3,new QTableWidgetItem(name));
            ui->tableWidget->setItem(count++,4,new QTableWidgetItem(number));
        }while (!file2.atEnd());
    }
    else
        qDebug()<<QObject::tr("打开失败");
    file2.close();
}

void Journal::receiveJournal() //从时间返回日志的槽
{
    this->show();
    ui->tableWidget->clear();
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"类别"<<"时间"<<"编号"<<"名称"<<"数量");
    if(ui->OutradioButton->isChecked()==false && ui->AllradioButton->isChecked()==false)   //判断radioBox情况
    {
        QFile file1("Input.txt");
        //判断文件是否存在
        if(file1.exists())
        {
            qDebug()<<QObject::tr("入库文件已经存在！");
        }else
        {
            //提示成功
            qDebug()<<QObject::tr("入库文件创建成功！");
        }
        if(file1.open(QIODevice::ReadOnly | QIODevice::Text ))
       {

            int i=0;
            QString journaldate_1;
            do
            {
                journaldate_1=QString::fromLocal8Bit( file1.readLine().trimmed());
                QString str =journaldate_1.section(',',0,0);
                QString Ctime = journaldate_1.section(',', 1, 1);
                QString id = journaldate_1.section(',', 2, 2);
                QString name = journaldate_1.section(',', 3, 3);
                QString number = journaldate_1.section(',', 4, 4);
                if(t->startstr<=t->overstr)
                {
                    if(t->startstr<=Ctime && t->overstr>=Ctime)
                    {
                        ui->tableWidget->setItem(i,0,new QTableWidgetItem(str));
                        ui->tableWidget->setItem(i,1,new QTableWidgetItem(Ctime));
                        ui->tableWidget->setItem(i,2,new QTableWidgetItem(id));
                        ui->tableWidget->setItem(i,3,new QTableWidgetItem(name));
                        ui->tableWidget->setItem(i++,4,new QTableWidgetItem(number));
                    };
                }
                else
                {
                    if(t->overstr<=Ctime && t->startstr>=Ctime)
                    {
                        ui->tableWidget->setItem(i,0,new QTableWidgetItem(str));
                        ui->tableWidget->setItem(i,1,new QTableWidgetItem(Ctime));
                        ui->tableWidget->setItem(i,2,new QTableWidgetItem(id));
                        ui->tableWidget->setItem(i,3,new QTableWidgetItem(name));
                        ui->tableWidget->setItem(i++,4,new QTableWidgetItem(number));
                    };
                }
            }while (!file1.atEnd());
        }
        else {
            qDebug()<<QObject::tr("打开失败");
        }
        file1.close();
    }
    if(ui->InradioButton->isChecked()==false && ui->AllradioButton->isChecked()==false)    //判断radioBox情况
    {
        QFile file2("Output.txt");             //判断文件是否存在
        if(file2.exists())
        {
            qDebug()<<QObject::tr("出库文件已经存在！");
        }else
        {                                                    //提示成功
            qDebug()<<QObject::tr("出库文件创建成功！");
        }
        if (file2.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            int i=0;
            QString journaldate_2;
            do   //将文件内容传给日志
            {
                journaldate_2=QString::fromLocal8Bit(file2.readLine().trimmed());
                QString str =journaldate_2.section(',', 0, 0);
                QString Ctime = journaldate_2.section(',', 1, 1);
                QString id = journaldate_2.section(',', 2, 2);
                QString name = journaldate_2.section(',', 3, 3);
                QString number = journaldate_2.section(',', 4, 4);
                if(t->startstr<=t->overstr)   //判断时间大小
                {
                    if(t->startstr<=Ctime && t->overstr>=Ctime)  //在时间区域内筛选
                    {
                        ui->tableWidget->setItem(i,0,new QTableWidgetItem(str));
                        ui->tableWidget->setItem(i,1,new QTableWidgetItem(Ctime));
                        ui->tableWidget->setItem(i,2,new QTableWidgetItem(id));
                        ui->tableWidget->setItem(i,3,new QTableWidgetItem(name));
                        ui->tableWidget->setItem(i++,4,new QTableWidgetItem(number));
                    };
                }
                else
                {
                    if(t->overstr<=Ctime && t->startstr>=Ctime) //在时间区域内筛选
                    {
                        ui->tableWidget->setItem(i,0,new QTableWidgetItem(str));
                        ui->tableWidget->setItem(i,1,new QTableWidgetItem(Ctime));
                        ui->tableWidget->setItem(i,2,new QTableWidgetItem(id));
                        ui->tableWidget->setItem(i,3,new QTableWidgetItem(name));
                        ui->tableWidget->setItem(i++,4,new QTableWidgetItem(number));
                    };
                }
            }while (!file2.atEnd());
        }
        else
            qDebug()<<QObject::tr("打开失败");
        file2.close();
    }
    if(ui->OutradioButton->isChecked()==false && ui->InradioButton->isChecked()==false)   //判断radioBox情况
    {
        int i=0;
        QFile file1("Input.txt");      //判断文件是否存在
        if(file1.exists())
        {
            qDebug()<<QObject::tr("入库文件已经存在！");
        }else
        {
            //提示成功
            qDebug()<<QObject::tr("入库文件创建成功！");
        }
        if(file1.open(QIODevice::ReadOnly | QIODevice::Text ))
       {
            QString journaldate_1;
            do  //将文件内容传给日志
            {
                journaldate_1=QString::fromLocal8Bit( file1.readLine().trimmed());
                QString str =journaldate_1.section(',',0,0);
                QString Ctime = journaldate_1.section(',', 1, 1);
                QString id = journaldate_1.section(',', 2, 2);
                QString name = journaldate_1.section(',', 3, 3);
                QString number = journaldate_1.section(',', 4, 4);
                if(t->startstr<=t->overstr)  //判断时间大小
                {
                    if(t->startstr<=Ctime && t->overstr>=Ctime)  //在时间区域内筛选
                    {
                        ui->tableWidget->setItem(i,0,new QTableWidgetItem(str));
                        ui->tableWidget->setItem(i,1,new QTableWidgetItem(Ctime));
                        ui->tableWidget->setItem(i,2,new QTableWidgetItem(id));
                        ui->tableWidget->setItem(i,3,new QTableWidgetItem(name));
                        ui->tableWidget->setItem(i++,4,new QTableWidgetItem(number));
                    };
                }
                else
                {
                    if(t->overstr<=Ctime && t->startstr>=Ctime)  //在时间区域内筛选
                    {
                        ui->tableWidget->setItem(i,0,new QTableWidgetItem(str));
                        ui->tableWidget->setItem(i,1,new QTableWidgetItem(Ctime));
                        ui->tableWidget->setItem(i,2,new QTableWidgetItem(id));
                        ui->tableWidget->setItem(i,3,new QTableWidgetItem(name));
                        ui->tableWidget->setItem(i++,4,new QTableWidgetItem(number));
                    };
                }
            }while (!file1.atEnd());
        }
        else {
            qDebug()<<QObject::tr("打开失败");
        }
        file1.close();
        QFile file2("Output.txt");   //判断文件是否存在
        if(file2.exists())
        {
            qDebug()<<QObject::tr("出库文件已经存在！");
        }else
        {                                                       //提示成功
            qDebug()<<QObject::tr("出库文件创建成功！");
        }
        if (file2.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QString journaldate_2;
            do        //将文件内容传给日志
            {
                journaldate_2=QString::fromLocal8Bit(file2.readLine().trimmed());
                QString str =journaldate_2.section(',', 0, 0);
                QString Ctime = journaldate_2.section(',', 1, 1);
                QString id = journaldate_2.section(',', 2, 2);
                QString name = journaldate_2.section(',', 3, 3);
                QString number = journaldate_2.section(',', 4, 4);
                if(t->startstr<=t->overstr)  //判断时间大小
                {
                    if(t->startstr<=Ctime && t->overstr>=Ctime)  //在时间区域内筛选
                    {
                        ui->tableWidget->setItem(i,0,new QTableWidgetItem(str));
                        ui->tableWidget->setItem(i,1,new QTableWidgetItem(Ctime));
                        ui->tableWidget->setItem(i,2,new QTableWidgetItem(id));
                        ui->tableWidget->setItem(i,3,new QTableWidgetItem(name));
                        ui->tableWidget->setItem(i++,4,new QTableWidgetItem(number));
                    };
                }
                else
                {
                    if(t->overstr<=Ctime && t->startstr>=Ctime)  //在时间区域内筛选
                    {
                        ui->tableWidget->setItem(i,0,new QTableWidgetItem(str));
                        ui->tableWidget->setItem(i,1,new QTableWidgetItem(Ctime));
                        ui->tableWidget->setItem(i,2,new QTableWidgetItem(id));
                        ui->tableWidget->setItem(i,3,new QTableWidgetItem(name));
                        ui->tableWidget->setItem(i++,4,new QTableWidgetItem(number));
                    };
                }
            }while (!file2.atEnd());
        }
        else
            qDebug()<<QObject::tr("打开失败");
        file2.close();
    }
}


void Journal::on_AllradioButton_clicked()
{
    ui->tableWidget->clear();
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"类别"<<"时间"<<"编号"<<"名称"<<"数量");
    count=0;
    QFile file1("Input.txt");
    //判断文件是否存在
    if(file1.exists())
    {
        qDebug()<<QObject::tr("入库文件已经存在！");
    }else
    {
        //提示成功
        qDebug()<<QObject::tr("入库文件创建成功！");
    }
    if(file1.open(QIODevice::ReadWrite | QIODevice::Text ))
   {
        QString journaldate_1;
        do   //将入货文件写入日志
        {
            journaldate_1=QString::fromLocal8Bit( file1.readLine().trimmed());
            QString str =journaldate_1.section(',',0,0);
            QString Ctime = journaldate_1.section(',', 1, 1);
            QString id = journaldate_1.section(',', 2, 2);
            QString name = journaldate_1.section(',', 3, 3);
            QString number = journaldate_1.section(',', 4, 4);

            ui->tableWidget->setItem(count,0,new QTableWidgetItem(str));
            ui->tableWidget->setItem(count,1,new QTableWidgetItem(Ctime));
            ui->tableWidget->setItem(count,2,new QTableWidgetItem(id));
            ui->tableWidget->setItem(count,3,new QTableWidgetItem(name));
            ui->tableWidget->setItem(count++,4,new QTableWidgetItem(number));
        }while (!file1.atEnd());
    }
    else {
        qDebug()<<QObject::tr("打开失败");
    }
    file1.close();
    QFile file2("Output.txt");
    //判断文件是否存在
    if(file2.exists())
    {
        qDebug()<<QObject::tr("出库文件已经存在！");
    }else
    {
        //提示成功
        qDebug()<<QObject::tr("出库文件创建成功！");
    }
    if (file2.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QString journaldate_2;
        do  //将出货文件写入日志
        {
            journaldate_2=QString::fromLocal8Bit(file2.readLine().trimmed());
            QString str =journaldate_2.section(',', 0, 0);
            QString Ctime = journaldate_2.section(',', 1, 1);
            QString id = journaldate_2.section(',', 2, 2);
            QString name = journaldate_2.section(',', 3, 3);
            QString number = journaldate_2.section(',', 4, 4);

            ui->tableWidget->setItem(count,0,new QTableWidgetItem(str));
            ui->tableWidget->setItem(count,1,new QTableWidgetItem(Ctime));
            ui->tableWidget->setItem(count,2,new QTableWidgetItem(id));
            ui->tableWidget->setItem(count,3,new QTableWidgetItem(name));
            ui->tableWidget->setItem(count++,4,new QTableWidgetItem(number));
        }while (!file2.atEnd());
    }
    else
        qDebug()<<QObject::tr("打开失败");
    file2.close();
}

void Journal::on_OutradioButton_clicked()
{
    ui->tableWidget->clear();
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"类别"<<"时间"<<"编号"<<"名称"<<"数量");
    QFile file2("Output.txt");
    //判断文件是否存在
    if(file2.exists())
    {
        qDebug()<<QObject::tr("出库文件已经存在！");
    }else
    {
        //提示成功
        qDebug()<<QObject::tr("出库文件创建成功！");
    }
    if (file2.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        int i=0;
        QString journaldate_2;
        do    //将出货文件写入日志
        {
            journaldate_2=QString::fromLocal8Bit(file2.readLine().trimmed());
            QString str =journaldate_2.section(',', 0, 0);
            QString Ctime = journaldate_2.section(',', 1, 1);
            QString id = journaldate_2.section(',', 2, 2);
            QString name = journaldate_2.section(',', 3, 3);
            QString number = journaldate_2.section(',', 4, 4);
            ui->tableWidget->setItem(i,0,new QTableWidgetItem(str));
            ui->tableWidget->setItem(i,1,new QTableWidgetItem(Ctime));
            ui->tableWidget->setItem(i,2,new QTableWidgetItem(id));
            ui->tableWidget->setItem(i,3,new QTableWidgetItem(name));
            ui->tableWidget->setItem(i++,4,new QTableWidgetItem(number));
        }while (!file2.atEnd());
    }
    else
        qDebug()<<QObject::tr("打开失败");
    file2.close();
}

void Journal::on_InradioButton_clicked()
{
    ui->tableWidget->clear();
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"类别"<<"时间"<<"编号"<<"名称"<<"数量");
    QFile file1("Input.txt");
    //判断文件是否存在
    if(file1.exists())
    {
        qDebug()<<QObject::tr("入库文件已经存在！");
    }else
    {
        //提示成功
        qDebug()<<QObject::tr("入库文件创建成功！");
    }
    if(file1.open(QIODevice::ReadOnly | QIODevice::Text ))
   {

        int i=0;
        QString journaldate_1;
        do  //将入库文件写入日志
        {
            journaldate_1=QString::fromLocal8Bit( file1.readLine().trimmed());
            QString str =journaldate_1.section(',',0,0);
            QString Ctime = journaldate_1.section(',', 1, 1);
            QString id = journaldate_1.section(',', 2, 2);
            QString name = journaldate_1.section(',', 3, 3);
            QString number = journaldate_1.section(',', 4, 4);
            ui->tableWidget->setItem(i,0,new QTableWidgetItem(str));
            ui->tableWidget->setItem(i,1,new QTableWidgetItem(Ctime));
            ui->tableWidget->setItem(i,2,new QTableWidgetItem(id));
            ui->tableWidget->setItem(i,3,new QTableWidgetItem(name));
            ui->tableWidget->setItem(i++,4,new QTableWidgetItem(number));
        }while (!file1.atEnd());
    }
    else {
        qDebug()<<QObject::tr("打开失败");
    }
    file1.close();
}

void Journal::on_pushButton_7_clicked()
{
    this->close();
}

void Journal::on_pushButton_8_clicked()//点击修改时间按钮
{
    t->show();
}
