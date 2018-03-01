#ifndef TOLINE_H
#define TOLINE_H
#include <QObject>
#include <QtMath>
#include <QPointF>
#include <QGraphicsItem>
#include <QLineF>
class ToLine
{
public:
    ToLine();
    //计算两点之间的距离
    qreal lineDis(qreal x1,qreal y1,qreal x2,qreal y2);
    //计算鼠标点到折线上相邻两点组成的线段的最短距离
    qreal countDisPoToLine(QPointF point,QPointF curPt,QPointF nextPt);
    //判断点是否在矩形内
    bool isPointInRect(QPointF point,QRectF bounds);
    //判断点是否在折线上，如果判断为真则在折线上生成离该点最近的点，否则返回鼠标点坐标
    QPointF isPointOnPloylineTest_02(QPointF point,QPolygonF polygon);
    //如果点离折线上某两点组成的线段最近，则在折线上生成与鼠标点最近的折线点
    QPointF getPointOnPolyline(QPointF point ,QPointF curPt,QPointF nextPt);


};

#endif // TOLINE_H
