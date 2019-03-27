#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "check.h"

loginWindow::loginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::loginWindow)
{
    ui->setupUi(this);
    //设置控件字体颜色
    ui->lineEditName->setStyleSheet("color:black");
    ui->lineEditPassword->setStyleSheet("color:black");
    ui->errorPassword->setStyleSheet("color:red");
    ui->lineEditPassword->setEchoMode(QLineEdit::Password);
    //初始化两个字符串
    name="";
    passWord="";

}

loginWindow::~loginWindow()
{
    delete ui;
}
//按下登录按钮
void loginWindow::on_pushButtonLogin_clicked()
{
    name=ui->lineEditName->text();
    passWord=ui->lineEditPassword->text();
    //导入文件
    QString fileName="User.txt";
    check pushButtonLogin(fileName);
    //检查帐号密码
    int canLogin=pushButtonLogin.canLogin(name,passWord);

    if(canLogin==1)
    {
        ui->errorPassword->setText("登录成功");
        ZHJ.show();
        this->close();
    }
    else if(canLogin==0)
    {
        ui->errorPassword->setText("密码错误");
    }
    else if(canLogin==2)
    {
        ui->errorPassword->setText("没有此帐号");
    }
}
//按下退出按钮
void loginWindow::on_pushButtonExit_clicked()
{
    exit(0);
}

void loginWindow::on_zhuce_clicked()
{
    ZC.show();
}
