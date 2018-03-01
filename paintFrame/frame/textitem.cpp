#include "textitem.h"
#include <QDebug>
TextItem::TextItem(QGraphicsItem *parent)
    : QGraphicsTextItem(parent)
{
    setDefaultTextColor(Qt::gray);
}
void TextItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    double scaleFactor = painter->matrix().m11();
    setTextWidth(textWidth()/scaleFactor);
    QFont font = this->font();
    qreal pointsize = 12;
    if(scaleFactor<1.872)
        pointsize = 12/scaleFactor;
    font.setPointSizeF(pointsize);
    this->setFont(font);
    QGraphicsTextItem::paint(painter,option,widget);
}
