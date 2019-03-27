#ifndef STOCK_SYSTEM_H
#define STOCK_SYSTEM_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QMenu>
#include "input.h"
#include "out_stock.h"
#include "mypaint.h"
#include "warning_line.h"
#include "journal.h"
#include <QDate>
namespace Ui {
class Stock_System;
}

class Stock_System : public QMainWindow
{
    Q_OBJECT
public:
    explicit Stock_System(QWidget *parent = nullptr);
    ~Stock_System();
    QSqlDatabase db;                     //数据库
    QSqlQuery query;                     //表的指针
    QString warnLine;                   //预警线
private:
    Input *clickImport;                 //进货窗口的指针
    Out_stock *clickOut;                //出货窗口的指针
    warning_line* warn;                 //设置预警线窗口指针
    Journal DZ;                         //断折的
public:
    Ui::Stock_System *ui;               //主窗口
    QSqlDatabase open_db(int n);             //创建打开数据库
    QSqlQuery create_query();           //创建查询表的指针
    void init_db();                     //将数据库展现在表格中
    int isnumber(QString src); //判断是否为数字
private slots:
    void hide_warning();                    //隐藏输入不合规范的警告
    void on_search();                          //搜索
    void on_home();                            //返回主页
    void on_input_clicked();                //进货
    void receive_new_input();               //新品入库
    void receive_old_input();               //老款进货
    void receive_output();                  //出库
    void receive_warning_line();
    void on_out_clicked();                  //点击出库
   // void on_actionformat_changed();         //改变预警线
    //void on_actionwarning_line_changed();
    void on_pushButton_4_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_7_clicked();
};

#endif // STOCK_SYSTEM_H
