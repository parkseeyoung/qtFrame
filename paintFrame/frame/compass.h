﻿#ifndef COMPASS_H
#define COMPASS_H

#include <QWidget>

class Compass : public QWidget
{
    Q_OBJECT
public:
    explicit Compass(QWidget *parent = 0);
    void paintEvent(QPaintEvent *event);
signals:

public slots:
};

#endif // COMPASS_H
