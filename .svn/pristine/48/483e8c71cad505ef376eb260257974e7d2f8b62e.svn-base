#include "lineitem.h"
#include <QDebug>
#include <QtMath>
#include <QStyleOptionGraphicsItem>
const qreal Pi = 3.141592654;
//临界点
const qreal threshold = 0.8;
LineItem::LineItem(StationPoint *startItem, StationPoint *endItem, LineType _linetype, QGraphicsItem *parent)
    : QGraphicsLineItem(parent)
{
    linetype = _linetype;
    myStartItem = startItem;
    myEndItem = endItem;
    ifAlarm = false;
    myColor = Qt::black;
    //QPen pen(myColor,4,Qt::DashDotDotLine,Qt::RoundCap,Qt::RoundJoin);
    //setPen(pen);
    //计算斜率
    QPointF headPoint = myStartItem->pos();
    QPointF endPoint = myEndItem->pos();
    qreal x1,y1,x2,y2;
    x1=headPoint.x();
    y1=headPoint.y();
    x2=endPoint.x();
    y2=endPoint.y();
    k = (y2-y1)/(x2-x1);
}

QRectF LineItem::boundingRect() const
{
    qreal extra = (pen().width() + 20) / 2.0;

    return QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(),
                                      line().p2().y() - line().p1().y()))
            .normalized()
            .adjusted(-extra,-extra,extra,extra);
}
void LineItem::createSignalMachinePainterPath()
{
    int count = signalMachinePoints.count();
    for (int i =0 ;i<count;i++)
    {
        signalMachinePoint &smPoint = signalMachinePoints[i];
        //在这上面加东西
        //找到谁是头
        QString tempname = myStartItem->x()>myEndItem->x()?myStartItem->station:myEndItem->station;
        qreal e;
        if(smPoint.deviceName.startsWith(tempname))
            e=90;
        else
            e=270;
        int deviceNum=smPoint.deviceName.toInt();
        qreal x0=smPoint.localPos.x();
        qreal y0=smPoint.localPos.y();
        QPointF pitem = moveToLine(x0,y0);
        QPainterPath path;
        if(deviceNum%2==1)
        {
            path.moveTo(0,0);
            path.lineTo(10,0);
            path.moveTo(5,0);
            path.lineTo(5,10);
            path.addEllipse(QRect(0,10,10,10));
        }
        else
        {
            path.moveTo(0,0);
            path.lineTo(10,0);
            path.moveTo(5,0);
            path.lineTo(5,10);
            path.addEllipse(QRect(0,10,10,10));
            e+=180;
        }
        QFont font(QString::fromLocal8Bit("宋体"));
        font.setBold(false);
        //font.setHintingPreference(QFont::PreferFullHinting);
        font.setPixelSize(10);
        path.addText(10,0,font,smPoint.deviceName);

        smPoint.onLinePos = pitem;
        smPoint.sPath = path;
        smPoint.e = e;
        //qDebug()<<smPoint.e<<smPoint.onLinePos;
    }
}

void LineItem::drawSignalMachine(QPainter *painter)
{
    //这个计算的过程其实可以缩减为一次！
    foreach (signalMachinePoint smPoint, signalMachinePoints)
    {
        QPointF pitem = smPoint.onLinePos;
        QPainterPath path = smPoint.sPath;
        qreal e = smPoint.e;
        QPen smpen;
        smpen.setWidth(1);
        smpen.setColor(Qt::gray);
        painter->save();
        painter->setPen(smpen);
        painter->setBrush(Qt::NoBrush);
        //旋转
        //有两点要求，1是要在方向的左边，第二是圆圈就是方向
        if(k==INFINITY)
        {
            path.translate(5,10);
            painter->translate(pitem);
            painter->rotate(-90);
        }
        else
        {
            path.translate(5,10);
            painter->translate(pitem);
            //还是四种情况
            painter->rotate(qAtan(k)*180/Pi+e);
            //painter->rotate(qAtan(k)*180/Pi+270);
        }
        painter->drawPath(path);
        painter->restore();
    }
}

QPainterPath LineItem::shape() const
{
    QPainterPath path = QGraphicsLineItem::shape();
    //这里加信号机，这里只是一个形状，就是用来规范线的区域范围，具体画线还是要在paint中
    //path.addPolygon(Linewidget);
    return path;
}

void LineItem::updatePosition()
{
    QLineF line(mapFromItem(myStartItem,0,0),mapFromItem(myEndItem,0,0));
    setLine(line);
}

void LineItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
//    //*?4*碰撞相交就返回
//   // if (myStartItem->collidesWithItem(myEndItem))
//   //     return;
    //放大的比例
    double scaleFactor = painter->matrix().m11();

    //放大比例束缚
    bool canChange;
    if(scaleFactor>1.872)
        canChange = true;
    else
    {
        canChange = false;
    }

    QPen myPen = pen();
    myPen.setColor(myColor);
    myPen.setCapStyle(Qt::SquareCap);
    painter->setRenderHint(QPainter::Antialiasing,true);
    if(linetype==StationLine)
    {
        //画警报
        if(ifAlarm)
        {
            QPen pen(Qt::red);
            painter->save();
            pen.setWidth(8);
            if(!canChange)
            pen.setWidthF(pen.widthF()/scaleFactor);

            painter->setBrush(QBrush(Qt::red));
            painter->setPen(pen);


            painter->drawLine(line());

            painter->restore();
        }
        //qreal arrowSize = 20;
        QBrush brush;
        brush.setTexture(image());
        myPen.setColor(QColor(165,165,165));
        myPen.setWidth(6);
        if(!canChange)
        myPen.setWidthF(myPen.widthF()/scaleFactor);

       // myPen.setBrush(brush);

        painter->setPen(myPen);
        painter->setBrush(Qt::NoBrush);

        painter->drawLine(line());
        //在这里设置一个类型，判断如果是铁路的话，就这样画
        myPen.setColor(QColor(22,22,22));
        myPen.setWidth(4);
        if(!canChange)
        myPen.setWidthF(myPen.widthF()/scaleFactor);

        QVector<qreal>dashes;
        qreal space = 4;
        dashes<<4<<space;
        //myPen.setDashOffset(8);
        myPen.setDashPattern(dashes);
        //myPen.setStyle(Qt::DashDotLine);
        painter->setPen(myPen);
        painter->drawLine(line());

        //
        painter->setPen(QPen(Qt::red));
    }
    if(linetype==CommonLine)
    {
        myPen.setCapStyle(Qt::RoundCap);
        myPen.setJoinStyle(Qt::RoundJoin);
        myPen.setWidth(6);
        if(!canChange)
        myPen.setWidthF(myPen.widthF()/scaleFactor);

        painter->setPen(myPen);
        painter->setBrush(Qt::NoBrush);
        painter->drawLine(line());
    }
    /*
     * 根据两点之间的坐标，计算某一个x坐标下的y坐标从而定位到线的边上
     */
    //如果是无穷大，说明直线竖起来了
    if(linetype!=StationLine)return;
    //画
    if(option->levelOfDetailFromTransform(painter->worldTransform()) > threshold)
        drawSignalMachine(painter);
}
QPointF LineItem::moveToLine(qreal x1,qreal y1)
{
    /*
     * 斜率我知道为k
     * 直线方程为 y-y0=k*(x-x0)。其垂线斜率为-1/k
     * 垂线的方程为：y-y1=-1/k(x-x1)
     * 则可以算出交点坐标
     */
    QPointF headPoint = myStartItem->pos();
    qreal x0=headPoint.x();
    qreal y0=headPoint.y();
    if(k==INFINITY)return QPointF(x0,y1);
    qreal qx=(k*(y1-y0)+x1+k*k*x0)/(k*k+1);
    qreal qy=k*(qx-x0)+y0;
    return QPointF(qx,qy);
}

QPixmap LineItem::image() const
{
    QPixmap pixmap(10,50);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    QPainterPath path;
    path.addRect(0,0,10,50);
    painter.setPen(QColor(165,165,165));
    painter.setBrush(QColor(165,165,165));
    painter.drawPath(path);
    //
    QPainterPath pathB;
    pathB.addRect(2,15,8,20);
    painter.setPen(QColor(22,22,22));
    painter.setBrush(QColor(22,22,22));
    painter.drawPath(pathB);

    return pixmap;
}
void LineItem::paintHuman()
{
    //因为人不知道有多少个可能会走到这条线上，所以需要考虑
    //将人的这个数组设置为静态的
//    foreach (PointItem *pitem, myHumans) {
//        if(LineItem.contains(pitem->pos()))

//    }
}
