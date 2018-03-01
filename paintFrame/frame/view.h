#ifndef VIEW_H
#define VIEW_H

#include <QFrame>
#include <QGraphicsView>
#include "myview.h"

QT_BEGIN_NAMESPACE
class QLabel;
class QSlider;
class QToolButton;
QT_END_NAMESPACE

class View;

class GraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    GraphicsView(View *v) : QGraphicsView(), view(v) {}
protected:
#ifndef QT_NO_WHEELEVENT
    void wheelEvent(QWheelEvent *) override;
#endif
    //双击放大
    void mouseDoubleClickEvent(QMouseEvent *event);
public:
   // QGraphicsScene *scene;
private:
    View *view;
};

class View : public QFrame
{
    Q_OBJECT
public:
    explicit View(const QString &name,QWidget *parent = 0);
    QGraphicsView *view() const;

public slots:
private slots:


private:
    GraphicsView *graphicsView;
    QLabel *label;
    QLabel *label2;
    QToolButton *searchBtn;
    QToolButton *resetButton;

};

#endif // VIEW_H
