#ifndef MYVIEW_H
#define MYVIEW_H
#include <QPainter>
#include <QPainterPath>
#include <QBasicTimer>
#include <QPolygonF>
#include <QGraphicsView>
#include <QPaintEvent>
#include "scene.h"

//这个类什么都不需要，只需要几个鼠标事件就行了

class  MyView : public QGraphicsView
{
    Q_OBJECT
public:
    MyView(QMenu *itemMenu);
private:
    QGraphicsScene *myscene;

    void wheelEvent(QWheelEvent *event);
    //拖动
//    void mousePressEvent(QWheelEvent *event);
//    void mouseReleaseEvent(QWheelEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);

public slots:
    void toItemPos(QString itemName);
protected:
    void resizeEvent(QResizeEvent *event) override
    {
        QGraphicsView::resizeEvent(event);
    }
};

#endif // MYVIEW_H
