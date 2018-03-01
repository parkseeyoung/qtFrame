#ifndef LEGEND_H
#define LEGEND_H

#include <QWidget>

class Legend : public QWidget
{
    Q_OBJECT
public:
    explicit Legend(QWidget *parent = 0);
    void paintEvent(QPaintEvent *event);
signals:

public slots:
};

#endif // LEGEND_H
