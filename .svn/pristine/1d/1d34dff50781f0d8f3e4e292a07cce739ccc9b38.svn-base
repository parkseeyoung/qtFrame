#ifndef HUMANPOINT_H
#define HUMANPOINT_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QMouseEvent>
class HumanPoint : public QObject,public QGraphicsItem
{
    Q_OBJECT
public:
    explicit HumanPoint(QString humanName,QObject *parent = 0);
    void timerEvent(QTimerEvent *event);
    //所有继承自QGraphicsItem的自定义图元都必须实现此函数
    QRectF boundingRect() const;

    //经纬度
    qreal jd;
    qreal wd;
    //公路
    QString fromStop;
    //人名
    QString senderName;
	QString id;
private:
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
signals:

public slots:

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int count;
    QRectF humanRect;
    qreal dx,dy;
private:
	//定时器ID
	int m_nTimerID;
	//缩放比例
	qreal lodScale;
	bool canChange;
public:
signals :
	void disappear(QString humanName);
	void onClicked();
};

#endif // HUMANPOINT_H
