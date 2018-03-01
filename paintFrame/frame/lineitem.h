#ifndef LINEITEM_H
#define LINEITEM_H

#include <QGraphicsLineItem>
#include <QPainter>
#include "stationpoint.h"
#include "humanpoint.h"
QT_BEGIN_NAMESPACE
class QGraphicsPolygonItem;
class QGraphicsScene;
class QRectF;
class QPainterPath;
QT_END_NAMESPACE
class StationPoint;
class signalMachinePoint
{
public:
    QString deviceName;
    QPointF localPos;
    signalMachinePoint(QString dn,QPointF lp):deviceName(dn),
        localPos(lp){}
    QPointF onLinePos;
    QPainterPath sPath;
    qreal e;
};

class signalMachinePoint;
class LineItem : public QGraphicsLineItem
{
public:
    enum { Type = UserType + 4};
    enum LineType{ CommonLine,StationLine};
    LineItem(StationPoint *startItem , StationPoint *endItem , LineType _linetype, QGraphicsItem *parent = 0);

    int type() const override {return Type;}
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void setColor(const QColor &color) { myColor = color;}
    StationPoint *startItem() const {return myStartItem;}
    StationPoint *endItem() const {return myEndItem;}

    void updatePosition();
    //人的集合
    //名字和信息
    static QHash<QString,HumanPoint*>myHumans;

    //根据数据画出信号机
    void drawSignalMachine(QPainter *painter);
    //数据在这里
    QList<signalMachinePoint>signalMachinePoints;

    //还有就是这个线的名字,信号机要根据这个名字找到线
    QString LineName;
    //还需要有线别来进行唯一确认
    QString xbName;
    void alarmOpen(){ifAlarm=true;}
    void alarmClose(){ifAlarm=false;}

    //判断信号机位置
    void createSignalMachinePainterPath();
private:
    StationPoint *myStartItem;
    StationPoint *myEndItem;
    QColor myColor;
    LineType linetype;
    //这里用来记录线上的一些小标记之类的东西
    //恩就用这个箭头来做事
    QPolygonF signalMachine;
    bool ifAlarm;



protected:
    void paint(QPainter*painter,const QStyleOptionGraphicsItem*option,
               QWidget*widget) override;
    QPointF moveToLine(qreal x1, qreal y1);
    qreal k;
    //画人
    void paintHuman();
    //画公路
    QPixmap image() const;
};

#endif // LINEITEM_H
