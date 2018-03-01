#include "view.h"
#include <QtWidgets>

void GraphicsView::mouseDoubleClickEvent(QMouseEvent *event)
{
    //双击放大
    qreal scaleFactor = this->matrix().determinant();

    qreal range=600;
    QPointF p = mapToScene(event->pos());
    qDebug()<<scaleFactor;
    if(scene()->itemAt(p,QTransform())==NULL)
    {
        if(scaleFactor >=1.838 || scaleFactor == 1.244)
            fitInView(sceneRect(),Qt::KeepAspectRatio);
        else if(scaleFactor<1.838)
        {
            //this->matrix().setMatrix(1.872,0,0,1.872,p.x(),p.y());
            fitInView(sceneRect(),Qt::KeepAspectRatio);
            fitInView(p.x()-range/2,p.y()-range/2,range,range,Qt::KeepAspectRatio);
        }
    }
    else {
        if(scene()->itemAt(p,QTransform())->cursor().shape()!=Qt::PointingHandCursor)
        {
            if(scaleFactor >=1.838 || scaleFactor == 1.244)
                //加一个adjusted
                fitInView(sceneRect(),Qt::KeepAspectRatio);
            else if(scaleFactor<1.838)
            {
                //this->matrix().setMatrix(1.872,0,0,1.872,p.x(),p.y());
                fitInView(sceneRect(),Qt::KeepAspectRatio);
                fitInView(p.x()-range/2,p.y()-range/2,range,range,Qt::KeepAspectRatio);
            }
        }
    }
    //QGraphicsView::mouseDoubleClickEvent(event);

	QList<QGraphicsItem*>itemList = this->view->view()->scene()->items();
	for each (QGraphicsItem *var in itemList)
	{
		var->update();
	}
	this->view->view()->viewport()->update();
	this->view->view()->scene()->update();
	//scale(1 / 1.2, 1 / 1.2);
	
}

#ifndef QT_NO_WHEELEVENT
void GraphicsView::wheelEvent(QWheelEvent *e)
{
        if (e->delta() > 0 && this->matrix().determinant()<3.0)
        {
           this->scale(1.1,1.1);
        }
		else if (e->delta() < 0 && this->matrix().determinant()>0.01)
        {
            this->scale(1.0/1.1,1.0/1.1);
        }
        e->accept();
}
#endif



View::View(const QString &name, QWidget *parent)
    : QFrame(parent)
{
    setFrameStyle(Sunken | StyledPanel);
    graphicsView = new GraphicsView(this);
    graphicsView->setRenderHint(QPainter::Antialiasing, true);

    graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
    graphicsView->setOptimizationFlags(QGraphicsView::DontSavePainterState);
    graphicsView->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
    graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

//    int size = style()->pixelMetric(QStyle::PM_ToolBarIconSize);
//    QSize iconSize(size,size);

//    resetButton = new QToolButton;
//    resetButton->setText(tr("0"));
//    resetButton->setEnabled(false);

    //
    QGridLayout *topLayout = new QGridLayout;
    topLayout->addWidget(graphicsView,0,0);
    setLayout(topLayout);
}
QGraphicsView *View::view() const
{
    return static_cast<QGraphicsView *>(graphicsView);
}