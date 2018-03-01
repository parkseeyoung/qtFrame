#ifndef TEXTITEM_H
#define TEXTITEM_H
#include <QGraphicsTextItem>
#include <QPainter>
#include <QGraphicsItem>
class TextItem : public QGraphicsTextItem
{
    Q_OBJECT

public:
    enum { Type = UserType + 3 };

    TextItem(QGraphicsItem *parent = 0);

    int type() const override {return Type;}
private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
signals:
    //鼠标移动，重新绘制

protected:
    //QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
};

#endif // TEXTITEM_H
