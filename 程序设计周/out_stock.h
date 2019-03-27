#ifndef OUT_STOCK_H
#define OUT_STOCK_H

#include <QDialog>
#include <QTimer>
namespace Ui {
class Out_stock;
}

class Out_stock : public QDialog
{
    Q_OBJECT

public:
    explicit Out_stock(QWidget *parent = nullptr);
    ~Out_stock();
    QString get_number();                   //获取数量
    int getstatus();                        //获取现在状态：编号还是名称
    QString get_id();                       //获取编号
    void out_warning();                     //给出信号警告
    void warning_hide();                    //隐藏警告
    void out_success();                     //出库成功
    QString get_name();                     //获取名称
    void clear();                           //清空输入栏
    void able();

private:
    Ui::Out_stock *ui;
signals:
    void out_vary_data();                   //改变出库的信号
private slots:
    void on_out_button_clicked();           //点击按钮
    void on_pushButton_6_clicked();
};

#endif // OUT_STOCK_H
