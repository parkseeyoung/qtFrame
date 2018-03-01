#include "polyline.h"
#include <QPainter>
PolyLine::PolyLine(QPainterPath path, QGraphicsItem *parent)
    :QGraphicsItem(parent)
{
    myPolygon = path.toFillPolygon();
}
QRectF PolyLine::boundingRect()const
{
    return myPolygon.boundingRect();
}
void PolyLine::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	double scaleFactor = painter->matrix().m11();
	bool canChange;
	if (scaleFactor>1.872)
		canChange = true;
	else
	{
		canChange = false;
	}
	painter->save();


	QPen pen;
	pen.setWidthF(1);
	if (!canChange)
	{
		pen.setWidthF(2 / scaleFactor);
	}
	pen.setColor(QColor(189, 179, 87, 255));
	painter->setPen(pen);
	QBrush brush(Qt::yellow);
	brush.setColor(QColor(189, 179, 87, 255));
	painter->setBrush(brush);
	painter->drawPolyline(myPolygon);
	painter->restore();
}
