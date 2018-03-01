#include "roadpath.h"

RoadPath::RoadPath(QPainterPath p_Path)
{
    myPolygon = p_Path.toFillPolygon();
}
void RoadPath::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    double scaleFactor = painter->matrix().m11();
    bool canChange;
    if(scaleFactor>1.872)
        canChange = true;
    else
    {
        canChange = false;
    }
    //设置笔宽
    QPen pen = this->pen();
    pen.setWidthF(1.8);
    setPen(pen);
    qreal penWidth = pen.widthF();
    if(!canChange)
    {
        pen.setWidthF(penWidth/scaleFactor);
    }
    pen.setColor(QColor(189,179,87,255));

    setPen(pen);
    setPolygon(myPolygon);
    QGraphicsPolygonItem::paint(painter,option,widget);
}
QRectF RoadPath::boundingRect()const
{
	return myPolygon.boundingRect();
}