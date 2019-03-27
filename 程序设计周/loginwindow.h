#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include <stock_system.h>//张xx的
#include "zhuce.h"


namespace Ui {
class loginWindow;
}

class loginWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit loginWindow(QWidget *parent = nullptr);
    ~loginWindow();

private slots:

    void on_pushButtonLogin_clicked();

    void on_pushButtonExit_clicked();

    void on_zhuce_clicked();

private:
    Ui::loginWindow *ui;
//获取的用户名
    QString name;
//获取的密码
    QString passWord;
//张xx的
    Stock_System ZHJ;
//注册窗口
    zhuce ZC;

};


#endif // LOGINWINDOW_H
