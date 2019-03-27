#ifndef INPUT_H
#define INPUT_H

#include <QDialog>
#include <QTimer>

namespace Ui {
class Input;
}

class Input : public QDialog
{
    Q_OBJECT

public:
    explicit Input(QWidget *parent = nullptr);
    ~Input();
    QString get_id(int id_);          //获取id
    QString get_name(int name_);       //获取名称
    QString get_category();            //获取分类
    QString get_number(int num_);      //获取进货数
    void add_success();
    void warning(QString s);
    void warning_3();
    int getstatus();           //获取状态
    void changesuccess();       //修改成功
    void clear();
    void able();
  //  void unable_push(QString button);

private:
    Ui::Input *ui;
signals:
    void sendvarydata_1();         //接受新品信号
    void sendvarydata_2();         //接受老款信号

/*private slots:
    void on_send_clicked();*/
public slots:
    void on_send_1_clicked();       //新品提交
    void hidewarning();             //新品信息不完整
    void hidewarning_2();            //老款信息不完整
    void on_send_2_clicked();       //老款进货
private slots:
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
};

#endif // INPUT_H
