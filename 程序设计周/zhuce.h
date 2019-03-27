#ifndef ZHUCE_H
#define ZHUCE_H

#include <QDialog>
#include <QFile>
#include <QTextStream>
#include <QCryptographicHash>//用于密码加密
#include "check.h"//检查重复



namespace Ui {
class zhuce;
}

class zhuce : public QDialog
{
    Q_OBJECT

public:
    explicit zhuce(QWidget *parent = nullptr);
    ~zhuce();

private slots:
    void on_fanhuiBt_clicked();

    void on_zhuceBt_clicked();

private:
    Ui::zhuce *ui;

};

#endif // ZHUCE_H
