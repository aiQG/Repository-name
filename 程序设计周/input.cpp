#include "input.h"
#include "ui_input.h"
#include "stock_system.h"
#include <QTimer>
#include <iostream>
using namespace std;

Input::Input(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Input)
{
    ui->setupUi(this);
    //设置字体黑色
    ui->Linenumber->setStyleSheet("color:black");
    ui->Linenumber_2->setStyleSheet("color:black");
    ui->Linevar->setStyleSheet("color:black");
    ui->LineId_1->setStyleSheet("color:black");
    ui->Linecategory->setStyleSheet("color:black");
    ui->Linename_1->setStyleSheet("color:black");
    ui->comboBox->setStyleSheet("color:black");
    ui->label->setStyleSheet("color:black");
    ui->label_2->setStyleSheet("color:black");
    ui->label_3->setStyleSheet("color:black");
    ui->label_4->setStyleSheet("color:black");
    ui->send_1->setStyleSheet("color:black");
    ui->send_2->setStyleSheet("color:black");
    ui->label_5->setStyleSheet("color:black");
    ui->pushButton_6->setStyleSheet("color:black");
    ui->pushButton_7->setStyleSheet("color:black");
    ui->tabWidget->setStyleSheet("color:black");

    //设置透明
    this->setWindowOpacity(1); //窗口整体透明度，0-1 从全透明到不透明
    this->setWindowFlags(Qt::FramelessWindowHint); //设置无边框风格
    this->setAttribute(Qt::WA_TranslucentBackground); //设置背景透明，允许鼠标穿透
    //插入图片
    ui->widget->setStyleSheet("#widget{background-image: url(:/image/p.png);}");
    //设定窗口大小
    setFixedSize(611,451);

    this->hide();

}

Input::~Input()
{
    delete ui;
}

//点击提交进行新品数据处理
void Input::on_send_1_clicked()
{
    emit sendvarydata_1();
}

//点击提交进行老款数据处理
void Input::on_send_2_clicked()
{
    emit sendvarydata_2();
}

//获取id（两种）
QString Input::get_id(int id_)
{
    QString id;
    if (id_==1)
    {
         id=ui->LineId_1->text();
    }
    else
    {
        id=ui->Linevar->text();
    }
    return id;
}

//获取名称
QString Input::get_name(int name_)
{
    QString name;
    if (name_==1)
    {
         name=ui->Linename_1->text();
    }
    else
    {
        name=ui->Linevar->text();
    }
    return name;
}

//获取类型
QString Input::get_category()
{
    QString category=ui->Linecategory->text();
    return category;
}

//获取数量
QString Input::get_number(int num_)
{
    QString number;
    if(num_==1)
    {
        number=ui->Linenumber->text();
    }
    else
    {
        number=ui->Linenumber_2->text();
    }
    return number;
}

//添加成功
void Input::add_success()
{
    ui->warning_2->show();
    ui->warning_2->setText("添加成功！！");
    ui->warning_2->setStyleSheet("color:red;");
    ui->send_1->setDisabled(true);
    QTimer::singleShot(1000,this,SLOT(close()));
}

//警告
void Input::warning(QString s)
{
    ui->warning_2->show();
    ui->warning_2->setText(s);
    ui->warning_2->setStyleSheet("color:red;");
    QTimer::singleShot(3000,this,SLOT(hidewarning()));
}

//隐藏警告
void Input::hidewarning()
{
    ui->warning_2->hide();
}


//获取选项栏状态
int Input::getstatus()
{
    int status=ui->comboBox->currentIndex();
    return status;
}

//老款警告
void Input::warning_3()
{
    ui->label_6->show();
    ui->label_6->setText("请输入完整信息");
    ui->label_6->setStyleSheet("color:red;");
    QTimer::singleShot(3000,this,SLOT(hidewarning_2()));
}

//警告隐藏
void Input::hidewarning_2()
{
    ui->label_6->hide();
}

//老款进货成功
void Input::changesuccess()
{
    ui->label_6->show();
    ui->label_6->setText("修改成功！！");
    ui->label_6->setStyleSheet("color:red;");
    ui->send_2->setDisabled(true);
    QTimer::singleShot(1000,this,SLOT(close()));
}

//清空输入栏
void Input::clear()
{
    ui->LineId_1->clear();
    ui->Linename_1->clear();
    ui->Linenumber_2->clear();
    ui->Linecategory->clear();
    ui->Linename_1->clear();
    ui->Linevar->clear();
    ui->Linenumber->clear();
}

void Input::able()
{
    ui->send_1->setDisabled(false);
    ui->send_2->setDisabled(false);
}



void Input::on_pushButton_6_clicked()
{
    this->close();
}

void Input::on_pushButton_7_clicked()
{
    this->close();
}
