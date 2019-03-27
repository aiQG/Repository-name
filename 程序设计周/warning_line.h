#ifndef WARNING_LINE_H
#define WARNING_LINE_H

#include <QDialog>

namespace Ui {
class warning_line;
}

class warning_line : public QDialog
{
    Q_OBJECT

public:
    explicit warning_line(QWidget *parent = nullptr);
    ~warning_line();
    QString getnumber();

private:
    Ui::warning_line *ui;
signals:
    void send_warning_line();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
};

#endif // WARNING_LINE_H
