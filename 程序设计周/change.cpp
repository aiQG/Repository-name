#include "change.h"
#include "ui_change.h"
#include <QDate>
#include <QDebug>

Change::Change(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Change)
{
    ui->setupUi(this);
    Initialization(); //对时间进行初始化
    //设置字体黑色
    ui->overdateEdit->setStyleSheet("color:black");
    ui->startdateEdit->setStyleSheet("color:black");
    this->setStyleSheet("color:black");
    //设置透明
    this->setWindowOpacity(1); //窗口整体透明度，0-1 从全透明到不透明
    this->setWindowFlags(Qt::FramelessWindowHint); //设置无边框风格
    this->setAttribute(Qt::WA_TranslucentBackground); //设置背景透明，允许鼠标穿透
    //插入图片
    ui->widget->setStyleSheet("#widget{background-image: url(:/image/Jp.png);}");



    //设定窗口大小
    setFixedSize(447,279);
    this->hide();

}

Change::~Change()
{
    delete ui;
}

void Change::Initialization()    //实现初始化
{
    ui->overdateEdit->setMaximumDate(QDate::currentDate());
    ui->startdateEdit->setMaximumDate(QDate::currentDate());  //设置最大时间
    ui->startdateEdit->setDate(QDate::currentDate());
    ui->overdateEdit->setDate(QDate::currentDate());          //获取系统时间
    return;
}


void Change::on_okpushBtn_clicked()  //点击“确定”
{

    QDate startdate =ui->startdateEdit->date();  //获取开始时间数据
    startstr = startdate.toString("yyyy-MM-dd");
    QDate overdate = ui->overdateEdit->date();   //获取结束时间数据
    overstr = overdate.toString("yyyy-MM-dd");
    this->close();
    //emit showjournal();
    Initialization();
}

void Change::on_cancelpushBtn_clicked()  //点击“取消”
{
   this->close();  //关闭窗口
}
void Change::receiveTime()  //打开时间窗口的槽
{
    this->show();  //打开窗口
}

