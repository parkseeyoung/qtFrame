#ifndef ROADPATH_H
#define ROADPATH_H
#include <QGraphicsPolygonItem>
#include <QPainterPath>
#include <QPainter>
class RoadPath : public QGraphicsPolygonItem
{
public:
    enum { Type = UserType + 20 };
    explicit RoadPath(QPainterPath p_Path);
    int type() const override{return Type;}
protected:
    //形状
    QPolygonF myPolygon;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	QRectF boundingRect() const;
};

#endif // ROADPATH_H
