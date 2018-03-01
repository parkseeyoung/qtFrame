#include "humanpoint.h"
#include <QDebug>
#include <QCursor>
#include <QStyleOptionGraphicsItem>
#define TIMER_TIMEOUT (40*1000)

//同心圆之间的间隔
const qreal interval = 5;
HumanPoint::HumanPoint(QString humanName,QObject *parent) : QObject(parent)
{
	senderName = humanName;
    humanRect=QRectF(0, 0,50,50);
    startTimer(100);
    count = 1;
    setAcceptHoverEvents(true);
    setAcceptTouchEvents(true);
    setFlag(QGraphicsItem::ItemIsSelectable,true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
    setAcceptHoverEvents(true);
    dx = 0.000000001;
    dy = 0.000000001;
	m_nTimerID = this->startTimer(TIMER_TIMEOUT);
}
void HumanPoint::timerEvent(QTimerEvent *event)
{
    if(count==6)count=0;
    count++;
    if(count<3)
    {
        dx = 0.000000001;
        dy = 0.000000001;
    }
    else
    {
        dx = -0.000000001;
        dy = -0.000000001;
    }
    //这个函数真nice
    setPos(mapToParent(dx,dy));
	//超时
	if (event->timerId() == m_nTimerID)
	{
		emit disappear(senderName);
	}
}
QRectF HumanPoint::boundingRect() const
{
	return humanRect;
}
void HumanPoint::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	Q_UNUSED(widget)
	painter->save();

	const qreal lod = option->levelOfDetailFromTransform(painter->worldTransform());
	lodScale = lod;
	if (lod > 0.8)
		canChange = true;
	else
		canChange = false;
    //mmp有例子
    painter->setRenderHint(QPainter::Antialiasing, true);
	QPen pen(Qt::green);
	if (!canChange)
		pen.setWidthF(1/lod);
	else
	{
		pen.setWidthF(1);
	}
	painter->setPen(pen);
    painter->translate(boundingRect().width()/2,boundingRect().height()/2);
    for(int i = 0 ;i < count ;i++)
    {
		painter->drawEllipse(QRectF(-interval*i / 2 / lod, -interval*i / 2 / lod, interval*i / lod, interval*i / lod));
    }

	//写字
	QFont font;
	font.setWeight(1);
	font.setFamily(QString::fromLocal8Bit("宋体"));
	if (!canChange)
		font.setPointSizeF(12 / lod);
	else
		font.setPointSizeF(12);
	painter->setFont(font);
	painter->drawText(interval * 5/lod ,0 , senderName);

	painter->restore();
}

void HumanPoint::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	emit onClicked();
	QGraphicsItem::mouseReleaseEvent(event);
}
//hover
void HumanPoint::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    setCursor(QCursor(Qt::PointingHandCursor));
    QGraphicsItem::hoverEnterEvent(event);
}
