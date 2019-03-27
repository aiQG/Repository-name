#ifndef MYQLABEL_H
#define MYQLABEL_H
#include <QLabel>
#include <QString>
class mypaint :public QLabel
{
    Q_OBJECT
public:
    explicit mypaint(QWidget *parent=0);
    void changetext(QString text);
private slots:
    void paintEvent(QPaintEvent *event);
    void updateIndex();

private:
    int charWidth;
    int curIndex;
    QString showText;
};

#endif // MYQLABEL_H
