#ifndef JOURNAL_H
#define JOURNAL_H

#include <QDialog>
#include "change.h"
#include <QFile>
#include <QTextStream>


namespace Ui {
class Journal;
}

class Journal : public QDialog
{
    Q_OBJECT

public:
    explicit Journal(QWidget *parent = nullptr);
    ~Journal();

    void inputJournal();//为了更新
private slots:

    void receiveJournal();  //返回日志槽


    void on_AllradioButton_clicked();//勾选全部

    void on_OutradioButton_clicked();//勾选出库

    void on_InradioButton_clicked();//勾选入库

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

signals:
    void TIMshow();  //打开时间窗口信号

private:
    Ui::Journal *ui;
    Change *t; //修改时间窗口指针
    int count; //用于计数
};

#endif //JOURNAL_H
