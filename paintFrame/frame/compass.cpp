#include "compass.h"
#include <QPainter>
Compass::Compass(QWidget *parent) : QWidget(parent)
{
    setMaximumSize(80,80);
    setMinimumSize(80,80);
    resize(60,60);
}
void Compass::paintEvent(QPaintEvent *event)
{
    //自己画
    QPainter painter(this);


    painter.setRenderHint(QPainter::Antialiasing,true);
    QPen pen(Qt::red);
    painter.setPen(pen);
    QBrush brush(Qt::red);
    painter.setBrush(brush);

    //写字
    pen.setColor(QColor(192,160,128));
    painter.setPen(pen);
    painter.drawText(34,15,QString::fromLocal8Bit("北"));

    pen.setColor(QColor(160,160,164));
    painter.setPen(pen);
    painter.drawText(5,44,QString::fromLocal8Bit("西"));

    pen.setColor(QColor(160,160,164));
    painter.setPen(pen);
    painter.drawText(34,75,QString::fromLocal8Bit("南"));

    pen.setColor(QColor(160,160,164));
    painter.setPen(pen);
    painter.drawText(66,44,QString::fromLocal8Bit("东"));

    painter.translate(15,15);

    painter.drawRect(15,15,20,20);

    pen.setColor(Qt::black);
    brush.setColor(Qt::black);
    painter.setPen(pen);
    painter.setBrush(brush);
    painter.drawRect(19,19,12,12);

    pen.setColor(Qt::gray);
    brush.setColor(Qt::gray);
    painter.setPen(pen);
    painter.setBrush(brush);
    painter.drawRect(21,21,8,8);

    QPainterPath path;
    path.moveTo(22,15);
    path.lineTo(25,0);
    path.lineTo(28,15);
    path.lineTo(22,15);

    path.moveTo(15,22);
    path.lineTo(0,25);
    path.lineTo(15,28);
    path.lineTo(15,22);


    path.moveTo(35,22);
    path.lineTo(50,25);
    path.lineTo(35,28);
    path.lineTo(35,22);

    path.moveTo(22,35);
    path.lineTo(25,50);
    path.lineTo(28,35);
    path.lineTo(22,35);

    pen.setColor(Qt::gray);
    brush.setColor(Qt::gray);
    painter.setPen(pen);
    painter.setBrush(brush);

    painter.drawPath(path);



}
