#ifndef STATIONPOINT_H
#define STATIONPOINT_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsSceneContextMenuEvent>
#include <QMenu>
#include <QPainter>
#include <QList>
#include <QMouseEvent>
#include "lineitem.h"

class LineItem;
class StationPoint : public QObject,public QGraphicsItem
{
    Q_OBJECT
public:
    enum PointType{Human,Station,PathPoint,PathPointWithImg};   //人，站，带图片的连接点
    StationPoint(PointType pointType,QMenu *contextMenu,QObject *parent = 0);

    PointType pointType() const {return myPointType;}

    int type()const override{return Type;}

    QRectF boundingRect()const;

    QPainterPath shape()const;

    void addLine(LineItem *line);

    //点的基本信息
    QString locator;
    QString station;
    QString devicename;
    QString devicetype;
    qreal jd;
    qreal wd;
    QString xb;
    QString dwname;
    int id;
    //greenPoint
    QString picname;
    QString routename;
    QString roadtype;
    QString dianwuduan;
	QString pguid;
	void setAlarm(bool alarmCheck){ alarm = alarmCheck; }

	int textPos;

private:

    PointType myPointType;

    QMenu *myContextMenu;

    QRectF pointRect;

    bool canChange;

    qreal lodScale;

	//red alarm
	bool alarm;
private:

    void drawHuman(QPainterPath *path);

	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:

    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;
};

#endif // STATIONPOINT_H
