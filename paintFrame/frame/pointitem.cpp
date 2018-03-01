#include "pointitem.h"
#include <QDebug>
int PointItem::count = 0;
//同心圆之间的间隔
const qreal interval = 5;
PointItem::PointItem(PointType pointType, QMenu *contextMenu,
                       QGraphicsItem *parent)
              : QGraphicsPolygonItem(parent)
{
    //setAttribute(Qt::WA_MouseTracking);
    setAcceptHoverEvents(true);
    myPointType = pointType;
    myContextMenu = contextMenu;

    //太好用了
        QPainterPath path;
        QRectF rectPath(QPoint(-10,-10),QPoint(10,10));
        QRectF greenRect(QPoint(-8,-8),QPoint(8,8));
    //
    switch (myPointType) {
    case Station:
        path.addEllipse(rectPath);
        myPolygon = path.toFillPolygon();
        break;
    case PathPoint:
        path.addEllipse(-1,-1,1,1);
        break;
    case PathPointWithImg:
        path.addRect(greenRect);
        myPolygon = path.toFillPolygon();
        break;
    case Human:
        path.addEllipse(greenRect);
        myPolygon = path.toFillPolygon();
        break;
    default:
        break;
    }
    setCacheMode(QGraphicsItem::DeviceCoordinateCache);
    setPolygon(myPolygon);
    //这三个是设置item被选中时的样式，但是我不需要它移动，我只需要重绘
    //setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    //setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}
void PointItem::removeLine(LineItem *line)
{
    int index = lines.indexOf(line);

    if( index != -1)
    {
        lines.removeAt(index);
    }
}

void PointItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    scene()->clearSelection();
    setSelected(true);
    myContextMenu->exec(event->screenPos());
}
void PointItem::addLine(LineItem *line)
{
    lines.append(line);
}
void PointItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
    myContextMenu->actions().at(0)->trigger();
}
void PointItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //放大的比例
    double scaleFactor = painter->matrix().m11();
    //懂了，画圆的话不是pen的宽度了而是半径的问题了
    QRectF rectPath(QPoint(-7,-7),QPoint(7,7));
    QPainterPath path;
    QPointF oldCenter=rectPath.center();
    bool canChange;
    if(scaleFactor>1.872)
        canChange = true;
    else
    {
        canChange = false;
    }
    if(!canChange)
    {
        rectPath.setWidth(rectPath.width()/scaleFactor);
        rectPath.setHeight(rectPath.height()/scaleFactor);
        rectPath.moveCenter(oldCenter);
    }
    if(myPointType == Station)
    {
        path.addEllipse(rectPath);
    }
    else if(myPointType == PathPointWithImg)
    {
        path.addRect(rectPath);
    }
    //path.closeSubpath();


    myPolygon=path.toFillPolygon();
    setPolygon(myPolygon);
    QGraphicsPolygonItem::paint(painter,option,widget);

    //咳直接在这给他把名字加上去
    QPainterPath path2;
    QFont font;
    font.setWeight(10);
    path2.addText(7,0,font,this->station);
    myPolygon=path2.toFillPolygon();
}
void PointItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    setCursor(QCursor(Qt::PointingHandCursor));
    QGraphicsItem::hoverEnterEvent(event);
}
