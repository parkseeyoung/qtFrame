#ifndef POINTITEM_H
#define POINTITEM_H
#include <QGraphicsPolygonItem>
#include <QGraphicsScene>
#include <QMenu>
#include <QPainter>
#include <QGraphicsSceneContextMenuEvent>
#include <QGraphicsItem>
#include <QList>
#include <QMouseEvent>
#include "lineitem.h"
class LineItem;
class PointItem : public QGraphicsPolygonItem
{
public:
    enum { Type = UserType + 15 };
    enum PointType{Human,Station,Semaphores,PathPoint,PathPointWithImg};   //人，站，信号机，连接点，带图片的连接点
    PointItem(PointType pointType, QMenu *contextMenu, QGraphicsItem *parent = 0);

    void removeLine(LineItem *line);
    void removeLines();

    PointType pointType() const { return myPointType; }

    void addLine(LineItem *line);

    void drawHuman(QPainterPath *path);

    static void addCount(){count++;}

    static int count;

    int type()const override{return Type;}


protected:
    //鼠标左键弹出菜单框
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;
private:
    PointType myPointType;
    QPolygonF myPolygon;
    QMenu *myContextMenu;
    //用来保存点
    QList<LineItem *>lines;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    //画人点专用
public:
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
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);

};

#endif // POINTITEM_H
