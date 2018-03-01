#ifndef POLYLINE_H
#define POLYLINE_H
#include <QGraphicsItem>

class PolyLine : public QGraphicsItem
{
public:
    PolyLine(QPainterPath path, QGraphicsItem *parent = 0);
    QRectF boundingRect()const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    QPolygonF myPolygon;
};

#endif // POLYLINE_H
