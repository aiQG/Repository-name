#include<QPainter>

#include"mypaint.h"

#include<QDebug>

#include<QtWidgets/qframe.h>

#include<QWidget>

#include<QTimer>

#include<sys/time.h>
#include <QLabel>




mypaint::mypaint(QWidget*parent) :QLabel(parent)

{

    curIndex =0;

    showText ="hello";





    charWidth=fontMetrics().width("a");



    QTimer *timer =new QTimer(this);



   connect(timer,SIGNAL(timeout()),this,SLOT(updateIndex()));

    timer->start(300);

}



void mypaint::paintEvent(QPaintEvent*event)

{

    QPen pen;

    QPainter painter(this);



    pen.setColor(QColor(255,0,255));

    pen.setStyle(Qt::DashDotDotLine);

    QFont font("楷体",20,QFont::Bold);

    painter.setPen(pen);

    painter.setFont(font);

   painter.drawText(0,50,showText.mid(curIndex));

   painter.drawText(width()-charWidth*curIndex,50,showText.left(curIndex));



}



void mypaint::updateIndex()

{

    update();

    curIndex++;

    if(curIndex*charWidth>width())

        curIndex =0;

}

void mypaint::changetext(QString text)
{
    showText=text;
}
