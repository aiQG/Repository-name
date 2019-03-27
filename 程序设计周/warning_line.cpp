#include "warning_line.h"
#include "ui_warning_line.h"

warning_line::warning_line(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::warning_line)
{
    ui->setupUi(this);
    this->setStyleSheet("color:black");


    //设置透明
    this->setWindowOpacity(1); //窗口整体透明度，0-1 从全透明到不透明
    this->setWindowFlags(Qt::FramelessWindowHint); //设置无边框风格
    this->setAttribute(Qt::WA_TranslucentBackground); //设置背景透明，允许鼠标穿透
    //插入图片
    ui->widget->setStyleSheet("#widget{background-image: url(:/image/warning.png);}");



    //设定窗口大小
    setFixedSize(400,300);


}

warning_line::~warning_line()
{
    delete ui;
}

QString warning_line::getnumber()
{
    return ui->lineEdit->text();
}

void warning_line::on_pushButton_clicked()
{
    emit send_warning_line();
}

void warning_line::on_pushButton_2_clicked()
{
    this->close();
}
