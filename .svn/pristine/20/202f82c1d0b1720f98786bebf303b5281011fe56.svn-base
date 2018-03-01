#include "myview.h"

MyView::MyView(QMenu *itemMenu )
{
    setRenderHint(QPainter::Antialiasing,true);
    myscene = new QGraphicsScene(this);


    setScene(myscene);
    setDragMode(QGraphicsView::ScrollHandDrag);
    fitInView(sceneRect(),Qt::KeepAspectRatio);
    setOptimizationFlags(QGraphicsView::DontSavePainterState);
    setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    scale(1.9,1.9);
}
void MyView::wheelEvent(QWheelEvent *event)
{
    //当前放缩倍数
    qreal scaleFactor = this->matrix().m11();
    qDebug()<<scaleFactor;
    if(event->delta() > 0 && scaleFactor<4)
    {
        scale(1.2,1.2); //2
    }
    else if(event->delta()<0 && scaleFactor>0.1)
    {
        scale(1.0/1.2,1.0/1.2);
    }
    event->accept();
    return;
}
void MyView::mouseDoubleClickEvent(QMouseEvent *event)
{
    //双击放大
    qreal scaleFactor = this->matrix().determinant();

    qreal range=1000;
    QPointF p = mapToScene(event->pos());
    qDebug()<<scaleFactor;
    if(myscene->itemAt(p,QTransform())==NULL)
    {
        if(scaleFactor >=1.838 || scaleFactor == 1.244)
            fitInView(sceneRect(),Qt::KeepAspectRatio);
        else if(scaleFactor<1.838)
        {
            //this->matrix().setMatrix(1.872,0,0,1.872,p.x(),p.y());
            fitInView(sceneRect(),Qt::KeepAspectRatio);
            fitInView(p.x()-range/2,p.y()-range/2,range/2,range/2,Qt::KeepAspectRatio);
        }
    }
    else {
        if(myscene->itemAt(p,QTransform())->cursor().shape()!=Qt::PointingHandCursor)
        {
            if(scaleFactor >=1.838 || scaleFactor == 1.244)
                //加一个adjusted
                fitInView(sceneRect(),Qt::KeepAspectRatio);
            else if(scaleFactor<1.838)
            {
                //this->matrix().setMatrix(1.872,0,0,1.872,p.x(),p.y());
                fitInView(sceneRect(),Qt::KeepAspectRatio);
                fitInView(p.x()-range/2,p.y()-range/2,range/2,range/2,Qt::KeepAspectRatio);
            }
        }
    }
    QGraphicsView::mouseDoubleClickEvent(event);
}
void MyView::toItemPos(QString itemName)
{
    qDebug()<<sceneRect();
    this->fitInView(sceneRect(),Qt::KeepAspectRatio);
//    if(myscene->myitems.contains(itemName))
//    {
//        qreal sidel = 500;
//        QPointF m_pos = myscene->myitems[itemName]->pos();
//        myscene->myitems[itemName]->focusItem();
//        this->fitInView(QRect(m_pos.x()-sidel/2,m_pos.y()-sidel/2,sidel,sidel),Qt::KeepAspectRatio);
//    }

}
