#include "zhuce.h"
#include "ui_zhuce.h"

zhuce::zhuce(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::zhuce)
{
    ui->setupUi(this);
    ui->mima->setEchoMode(QLineEdit::Password);
    ui->zhuceOk->setStyleSheet("color:red");
    this->setStyleSheet("color:black");
}

zhuce::~zhuce()
{
    delete ui;
}

void zhuce::on_fanhuiBt_clicked()
{
    this->close();
}

void zhuce::on_zhuceBt_clicked()
{
    QString mima=ui->mima->text();
    QString zhanghao=ui->zhanghao->text();
    //检查重复
    check First("User.txt");
    int PASS=First.canLogin(zhanghao,mima);
    if(PASS==1)
    {
        ui->zhuceOk->setText("帐号存在");
        return;
    }


    //开始注册

    QString fileName="User.txt";

    QByteArray byteArray;
    byteArray.append(mima);
    QCryptographicHash hash(QCryptographicHash::Md5);
    hash.addData(byteArray);
    QString pwdMD5 = hash.result().toHex();//加密，与正确密码对比



    QFile F(fileName);
    F.open(QIODevice::WriteOnly|QIODevice::Append);
    QTextStream f(&F);
    f<<zhanghao<<endl<<pwdMD5<<endl;
    F.close();

    ui->zhuceOk->setText("注册成功!");

}
