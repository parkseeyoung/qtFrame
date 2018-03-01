#ifndef SCENE_H
#define SCENE_H


#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlIndex>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>
#include <QVariant>
#include <QDebug>

#include <QGraphicsScene>
#include <QPainter>
#include <QMenu>
#include <QMouseEvent>
#include "pointitem.h"
#include "mydatabase.h"
#include <QGraphicsView>
#include <iostream>
#include <QScrollBar>
#include "textitem.h"
#include "humanpoint.h"
#include "myxml.h"
#include "toline.h"
#include "roadpath.h"
using namespace std;
class SignalMachinePointInfo
{
public:
    QString station;
    QString mapname;
    QString devicename;
    qreal jd;
    qreal wd;
    QString xb;
    QString dwname;
    explicit SignalMachinePointInfo(QString _station,QString _mapname,
                           QString _devicename,qreal _jd,qreal _wd,
                           QString _xb,QString _dwname):
        station(_station),mapname(_mapname),devicename(_devicename),
    jd(_jd),wd(_wd),xb(_xb),dwname(_dwname){;}

};


#endif // SCENE_H
