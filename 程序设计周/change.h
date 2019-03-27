#ifndef CHANGE_H
#define CHANGE_H

#include <QDialog>


namespace Ui {
class Change;
}

class Change : public QDialog
{
    Q_OBJECT

public:
    explicit Change(QWidget *parent = nullptr);
    ~Change();
    void Initialization();              //初始化，实现获取系统时间
    QString  startstr;
    QString  overstr;

private slots:
    void on_okpushBtn_clicked();      //确定按钮

    void on_cancelpushBtn_clicked();  //取消
    void receiveTime();  //打开时间窗口槽
signals:
    //void showjournal(); //打开日志窗口信号

private:
    Ui::Change *ui;

};

#endif // CHANGE_H
