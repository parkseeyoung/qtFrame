#include "legend.h"
#include <QPainter>
#include <QGraphicsView>
#include <QDebug>
Legend::Legend(QWidget *parent) : QWidget(parent)
{
    setMaximumSize(600,80);
    setMinimumSize(600,80);
    resize(600,80);
}
void Legend::paintEvent(QPaintEvent *event)
{
    //时钟的例子啊！！
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    QPen pen(Qt::gray);
    QBrush brush(Qt::black);

    painter.setRenderHint(QPainter::TextAntialiasing,true);
    painter.setPen(pen);
    painter.setBrush(brush);
    painter.drawRect(0,0,290,80);
    painter.drawRect(310,0,290,80);
    //qDebug()<<painter.font().pointSize();
    QFont font = painter.font();
    font.setPointSize(13);
    painter.setFont(font);
    painter.drawText(112,20,QString::fromLocal8Bit("符号释义"));


    font.setPointSize(9);
    painter.setFont(font);
    painter.drawText(30,40,QString::fromLocal8Bit("在路上"));
    painter.drawText(120,40,QString::fromLocal8Bit("故障车站"));
    painter.drawText(210,40,QString::fromLocal8Bit("故障区间"));

    QPainterPath path;
    path.moveTo(33,47);
    path.lineTo(53,57);
    path.lineTo(33,67);
    path.lineTo(40,57);
    path.lineTo(33,47);
    pen.setColor(Qt::red);
    pen.setWidth(1);
    painter.setPen(pen);
    brush.setColor(Qt::red);
    painter.setBrush(brush);
    //painter.drawPath(path);

    path.addEllipse(137,51,16,16);
    path.addRect(205,50,60,16);

    painter.drawPath(path);

    //颜色释义
    pen.setColor(Qt::gray);
    painter.setPen(pen);
    painter.translate(310,0);

    font.setPointSize(13);
    painter.setFont(font);
    painter.drawText(112,20,QString::fromLocal8Bit("颜色释义"));


    font.setPointSize(9);
    painter.setFont(font);

    painter.drawText(30,40,QString::fromLocal8Bit("无上道"));
    painter.drawText(115,40,QString::fromLocal8Bit("计划内上道"));
    painter.drawText(210,40,QString::fromLocal8Bit("无施工上道"));

    pen.setColor(Qt::gray);
    brush.setColor(Qt::gray);
    painter.setPen(pen);
    painter.setBrush(brush);
    painter.drawRect(32,50,28,16);


    pen.setColor(QColor(0,255,255));
    brush.setColor(QColor(0,255,255));
    painter.setPen(pen);
    painter.setBrush(brush);
    painter.drawRect(130,50,28,16);


    pen.setColor(Qt::yellow);
    brush.setColor(Qt::yellow);
    painter.setPen(pen);
    painter.setBrush(brush);
    painter.drawRect(225,50,28,16);

}
