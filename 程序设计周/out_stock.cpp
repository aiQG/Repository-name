#include "out_stock.h"
#include "ui_out_stock.h"
#include <QTimer>

Out_stock::Out_stock(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Out_stock)
{
    ui->setupUi(this);
    ui->out_number->setStyleSheet("color:black");
    ui->out_id_name->setStyleSheet("color:black");
    ui->out_cobox->setStyleSheet("color:black");
    ui->pushButton_6->setStyleSheet("color:black");
    ui->out_button->setStyleSheet("color:black");
    ui->out_cobox->setStyleSheet("color:black");
    ui->label->setStyleSheet("color:black");


    //设置透明
    this->setWindowOpacity(1); //窗口整体透明度，0-1 从全透明到不透明
    this->setWindowFlags(Qt::FramelessWindowHint); //设置无边框风格
    this->setAttribute(Qt::WA_TranslucentBackground); //设置背景透明，允许鼠标穿透
    //插入图片
    ui->widget->setStyleSheet("#widget{background-image: url(:/image/p.png);}");
    //设定窗口大小
    setFixedSize(481,368);

    this->hide();

}

Out_stock::~Out_stock()
{
    delete ui;
}

//发送信号，接受数据
void Out_stock::on_out_button_clicked()
{
    emit out_vary_data();
    ui->out_button->setDisabled(true);
}

//获取数量
QString Out_stock::get_number()
{
        QString number;
        number=ui->out_number->text();
        return number;
}

//获取选择框状态
int Out_stock::getstatus()
{
    int status=ui->out_cobox->currentIndex();
    return status;
}

//获取id
QString Out_stock::get_id()
{
    QString id;
    id=ui->out_id_name->text();
    return id;
}

//获取名称
QString Out_stock::get_name()
{
    QString name;
    name=ui->out_id_name->text();
    return name;
}

//输出警告
void Out_stock::out_warning()
{
    ui->out_warning->show();
    ui->out_warning->setText("请输入完整信息");
    ui->out_warning->setStyleSheet("color:red;");
    QTimer::singleShot(3000,this,SLOT(warning_hide()));
}

//隐藏警告
void Out_stock::warning_hide()
{
    ui->out_warning->hide();
}

//输出成功
void Out_stock::out_success()
{
    ui->out_warning->show();
    ui->out_warning->setText("修改成功");
    ui->out_warning->setStyleSheet("color:red;");
    ui->out_button->setDisabled(true);
    QTimer::singleShot(3000,this,SLOT(close()));
}

//清空输入栏
void Out_stock::clear()
{
    ui->out_id_name->clear();
    ui->out_number->clear();
}

void Out_stock::able()
{
    ui->out_button->setDisabled(false);
}


void Out_stock::on_pushButton_6_clicked()
{
    this->close();
}
