#include "check.h"

check::check(QString f)
{
    fName=f;
}

//检查用户名是否相同
int check::canLogin(QString name,QString pwd)
{
    //以只读方式打开文件
    QFile F(fName);
    F.open(QIODevice::ReadOnly | QIODevice::Text);

    QString realName;
    QString realPassword;
    while(!F.atEnd())
    {
        realName=F.readLine().trimmed();
        realPassword=F.readLine().trimmed();
        if( !QString::compare(realName,name) )
        {
            //MD5加密
            QByteArray byteArray;
            byteArray.append(pwd);
            QCryptographicHash hash(QCryptographicHash::Md5);
            hash.addData(byteArray);
            QString pwdMD5 = hash.result().toHex();//加密，与正确密码对比
            if(!QString::compare(realPassword,pwdMD5))
            {
                F.close();
                return 1;//可以登录
            }
            else
            {
                F.close();
                return 0;//密码错误
            }
        }
    }
    F.close();
    return 2;//没有帐号
}
