#include "toline.h"
/*
 * 这个类的主要功能就是将点移动到线上
 * 当然这有一个范围
 */

ToLine::ToLine()
{

}
qreal ToLine::lineDis(qreal x1, qreal y1, qreal x2, qreal y2)
{
    qreal lineLength = 0;
    lineLength = qSqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
    return lineLength;
}
qreal ToLine::countDisPoToLine(QPointF point, QPointF curPt,
                               QPointF nextPt)
{
    qreal dis = 0;
    qreal xCur = curPt.x();     //P1
    qreal yCur = curPt.y();
    qreal xNext = nextPt.x();   //P2
    qreal yNext = nextPt.y();
    //已知点的坐标                //P
    qreal xPoint = point.x();
    qreal yPoint = point.y();
    //P1到P的长度，记作线段b
    qreal lengthCurToPo = lineDis(xCur ,yCur ,xPoint,yPoint);
    //P2到P的长度，记作线段c
    qreal lengthNextToPo = lineDis(xNext,yNext,xPoint,yPoint);
    //P1到P2的长度，记作线段a
    qreal lengthCurToNext = lineDis(xCur, yCur ,xNext ,yNext);

    if(lengthNextToPo + lengthCurToPo == lengthCurToNext)
    {
        //当b+c=a时，P在P1和P2组成的线段上
        dis = 0;
        return dis;
    }
    else if (lengthNextToPo * lengthNextToPo >= lengthCurToNext *
             lengthCurToNext + lengthCurToPo*lengthCurToPo)
    {
        //当c*c>=a*a+b*b时组成直角三角形或钝角三角形，投影在P1延长线上
        dis = lengthCurToPo;
        return dis;
    }
    else if (lengthCurToPo * lengthCurToPo >= lengthCurToNext *
             lengthCurToNext + lengthNextToPo * lengthNextToPo)
    {
        //当b*b>c*c+a*a时组成直角三角形或钝角三角形，投影在p2延长线上
        dis = lengthNextToPo;
        return dis;
    }
    else
    {
        //其他情况组成锐角三角形，则求三角形的高
        qreal p = (lengthCurToPo + lengthNextToPo + lengthCurToNext) / 2; // 半周长
        qreal s = qSqrt(p * (p - lengthCurToNext) * (p - lengthCurToPo) * (p - lengthNextToPo));//海伦公式求面积
        dis = 2 * s / lengthCurToNext;  //  返回点到线的距离（利用三角形面积公式求高）
        return dis;
    }
}
bool ToLine::isPointInRect(QPointF point, QRectF bounds)
{
    return bounds.contains(point);
}
QPointF ToLine::isPointOnPloylineTest_02(QPointF point, QPolygonF polygon)
{
    //误差
    qreal dif = 10;
    // 首先判断点是否在线的外包矩形内，如果在，则进一步判断，否则返回false
    QRectF lineBounds = polygon.boundingRect().adjusted(-dif,-dif,dif,dif);
    if(!isPointInRect(point,lineBounds))
    {
        return point;
    }
    QList<qreal>disArray;   //储存最短距离
    QList<QPointF>pointArray;//储存折线相邻点
    QPointF curPt ; // 折线的两个相邻点
    QPointF nextPt;
    //这里用lines可以存储折线上的一系列点
    for(int i = 0; i < polygon.count()-1;i++)
    {
        curPt = polygon.at(i);
        nextPt = polygon.at(i+1);
        //计算鼠标点到该两个相邻点组成的线段的最短距离
        qreal dis = countDisPoToLine(point,curPt,nextPt);
        //先将存储最短距离的数组排序
        disArray.push_back(dis);
        qSort(disArray);
        if(dis == disArray[0])
        {
            pointArray.push_back(curPt);
            pointArray.push_back(nextPt);
        }
    }
    //取得数组最后两项，即为当最短距离最小时鼠标点两侧的折线点
    curPt = pointArray[pointArray.length()-2];
    nextPt = pointArray[pointArray.length()-1];


    //取得数组中最小的最短距离
    qreal disMin = disArray.at(0);
    //当最短距离小于误差值时，判断鼠标点在折线上（误差值可更改）
    if(disMin < dif && disMin >-dif)
        return getPointOnPolyline(point,curPt,nextPt);
    return point;
}

QPointF ToLine::getPointOnPolyline(QPointF point, QPointF curPt, QPointF nextPt)
{
    qreal dif = 1;
    qreal pointx,pointy;
    qreal precisionx = curPt.x() - nextPt.x();
    qreal precisiony = curPt.y() - nextPt.y();

    if(precisionx < dif && precisionx >-dif)
    {
        //当折线上两点x相同时（存在一定误差）

        pointx = curPt.x();
        pointy = point.y();
        //创建生成点对象
        return QPointF(pointx,pointy);
    }
    else if(precisiony < dif && precisiony>-dif)
    {
        //当折线上两点的y相同时（存在一定误差）
        pointx = point.x();
        pointy = curPt.y();
        return QPointF(pointx,pointy);
    }
    else
    {
        //斜率
        qreal k = (nextPt.y() - curPt.y()) / (nextPt.x() - curPt.x());
        /*
           求得该点到线段的垂足坐标
           设线段的两端点为pt1和pt2，斜率为：k = ( pt2.y - pt1. y ) / (pt2.x - pt1.x );
           该直线方程为：y = k* ( x - pt1.x) + pt1.y。其垂线的斜率为 - 1 / k，
           垂线方程为：y = (-1/k) * (x - point.x) + point.y
        */
        qreal pointx = (k * k * curPt.x() + k * (point.x() - curPt.x()) + point.x())/
                (k*k+1);
        qreal pointy = k*(pointx - curPt.x()) + curPt.y();
        return QPointF(pointx,pointy);
    }
}
