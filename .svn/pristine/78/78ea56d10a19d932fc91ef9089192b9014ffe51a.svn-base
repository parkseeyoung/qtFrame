#include "stationpoint.h"
#include <QDebug>
#include <QGraphicsScene>
#include <QStyleOptionGraphicsItem>
StationPoint::StationPoint(PointType pointType, QMenu *contextMenu, QObject *parent):myPointType(pointType)
{
    setAcceptHoverEvents(true);
    myContextMenu = contextMenu;
    pointRect = QRectF(-10,-10,30,20).adjusted(-1,-1,1,1);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
    setFlag(QGraphicsItem::ItemIsSelectable,true);

	setCacheMode(QGraphicsItem::NoCache);

    setFlag(QGraphicsItem::ItemClipsToShape);
    setFlags(ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
	alarm = false;
}
void StationPoint::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    scene()->clearSelection();
    setSelected(true);
    myContextMenu->exec(event->screenPos());
}

void StationPoint::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    setCursor(QCursor(Qt::PointingHandCursor));
    QGraphicsItem::hoverEnterEvent(event);
}

void StationPoint::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	Q_UNUSED(event);
	myContextMenu->actions().at(0)->trigger();
}

QRectF StationPoint::boundingRect() const
{
    //获取放大的比例
    //const qreal lod = option->levelOfDetailFromTransform(painter->worldTransform());
    switch (myPointType) {
    case Station:
        if(canChange)
            return QRectF(-100,-100,300,200).adjusted(-1,-1,1,1);
        else
            return QRectF(-100/lodScale,-100/lodScale,300/lodScale,200/lodScale).adjusted(-1,-1,1,1);
        break;
    case PathPointWithImg:
        return  QRectF(QPoint(-8,-8),QPoint(8,8));
    default:
        break;
    }
}

QPainterPath StationPoint::shape() const
{
    QPainterPath path;
    switch (myPointType) {
    case Station:
        if(canChange)
            path.addRect(-10,-10,20,20);
        else
            path.addRect(-10/lodScale,-10/lodScale,20/lodScale,20/lodScale);
        break;
    case PathPointWithImg:
        path.addRect(QRectF(QPoint(-8,-8),QPoint(8,8)));
    default:
        break;
    }

    return path;
}

void StationPoint::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	Q_UNUSED(widget)
	
	painter->save();

    //获取放大的比例
    painter->setRenderHint(QPainter::Antialiasing,true);
    const qreal lod = option->levelOfDetailFromTransform(painter->worldTransform());
    lodScale = lod;
    qDebug()<<lod;
    if(lod > 0.8)
        canChange = true;
    else
        canChange = false;
    QPainterPath path;
    QRectF rectPath;
    if(!canChange)
    {
        QRectF rectPathTemp(QPoint(-10/lod,-10/lod),QPoint(10/lod,10/lod));
        rectPath = rectPathTemp;
    }
    else
    {
        QRectF rectPathTemp(QPoint(-10,-10),QPoint(10,10));
        rectPath = rectPathTemp;
    }
    QRectF greenRect(QPoint(-8,-8),QPoint(8,8));
    QPen pen;
    QBrush brush(Qt::gray);
    QFont font;
    font.setWeight(1);
    font.setFamily(QString::fromLocal8Bit("宋体"));
    if(!canChange)
		font.setPointSizeF(12 / lod);
    else
		font.setPointSizeF(12);
    font.setStyleStrategy(QFont::ForceOutline);

	QFontMetrics fm(font);
	qreal startPoint = 10;
	if (textPos == 2)
		startPoint = -fm.width(station) - 10;
    
	if (alarm == false)
		switch (myPointType) {
		case Station:
			if(!canChange)
			{
				pen.setColor(Qt::gray);
				painter->setPen(pen);
				painter->setBrush(brush);
				painter->drawEllipse(rectPath);
				painter->setFont(font);
				painter->drawText(startPoint, 0, 200 / lod, 50 / lod, Qt::AlignJustify, station);
			}
			else
			{
				pen.setColor(Qt::gray);
				brush.setColor(Qt::black);
				painter->setPen(pen);
				painter->setBrush(brush);
				painter->drawEllipse(rectPath.adjusted(1, 1, -1, -1));
				painter->drawEllipse(rectPath.adjusted(3, 3, -3, -3));
				painter->drawPath(path);
				painter->setFont(font);
				painter->drawText(startPoint, 0, 200, 50, Qt::AlignJustify, station);
			}
			break;
		case Human:
			break;
		case PathPointWithImg:
			path.addRect(greenRect);
			pen.setColor(Qt::green);
			brush.setColor(Qt::green);
			painter->setPen(pen);
			painter->setBrush(brush);
			painter->drawPath(path);
			break;
		default:
			break;
		}
	else if (alarm == true)
	{
		switch (myPointType)
		{
		case Station:
			path.addEllipse(rectPath);
			pen.setColor(Qt::red);
			brush.setColor(Qt::red);
			painter->setPen(pen);
			painter->setBrush(brush);
			painter->drawPath(path);
			painter->setFont(font);
			if (!canChange)
				painter->drawText(startPoint, 0, 200 / lod, 50 / lod, Qt::AlignJustify, station);
			else
				painter->drawText(startPoint, 0, 200, 50, Qt::AlignJustify, station);
			break;
		case PathPointWithImg:
			path.addRect(greenRect);
			pen.setColor(Qt::green);
			brush.setColor(Qt::green);
			painter->setPen(pen);
			painter->setBrush(brush);
			painter->drawPath(path);
			break;
		default:
			break;
		}
	}
	painter->restore();
}
