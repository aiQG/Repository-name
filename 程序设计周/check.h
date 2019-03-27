#ifndef CHECK_H
#define CHECK_H
#include <QFile> //用于文件操作
#include <QCryptographicHash>//用于密码加密


//把文件导入 然后检查用户名密码
class check
{
public:
    check(QString);//参数是文件名
    int canLogin(QString,QString);

private:
    QString fName;

};

#endif // CHECK_H
