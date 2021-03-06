﻿#include "mainwidget.h"


#include <QHBoxLayout>
#include <QSplitter>
#include "Windows.h"
#include <QMessageBox>
#include "WinUser.h"
#include "polyline.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    scene = new QGraphicsScene();
	wordList.clear();
    //iniAll(QString::fromLocal8Bit("C:\\Users\\Chen-Liu\\Documents\\Qt_Project\\build-mypaint_x86-Desktop_Qt_5_8_0_MSVC2013_32bit-Debug\\Personinfo.mdb")
    //       ,QString::fromLocal8Bit("C:\\Users\\Chen-Liu\\Documents\\Qt_Project\\build-mypaint_x86-Desktop_Qt_5_8_0_MSVC2013_32bit-Debug\\GxData.mdb"));
}
void MainWidget::iniAll(QString PersoninfoPath,QString GxDataPath)
{
    m_pDB = new MyDataBase();
    createActions();
    createMenus();
    DB_PersoninfoPath = PersoninfoPath;
    DB_GxDataPath = GxDataPath;
    myItemType = StationPoint::Human;
    scene->setSceneRect(QRectF(0,0,9000,9000));
    scene->setBackgroundBrush(QBrush(Qt::black));
    if(!ConnectDB())exit(1);
    initData();
    toline = new ToLine;
    iniRoadPath();
    iniStationPoint();
    iniStationLine();
    //iniStationName();

    //窗口最大化
    setWindowState(Qt::WindowMaximized);
    setMinimumWidth(700);
    //放入View中
    view = new View("2");
    view->view()->setScene(scene);
    view->view()->scene()->update();
    QSplitter *h1Splitter = new QSplitter;
    h1Splitter->addWidget(view);
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(h1Splitter);
    setLayout(layout);
    //view->view()->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
    view->view()->fitInView(view->view()->sceneRect(),Qt::KeepAspectRatio);
    view->view()->scale(1.9,1.9);
	scene->update();

	//设置图例
	compass = new Compass(this);
	mylegend = new Legend(this);
	sl = new searchLine(this);
	sl->installEventFilter(this);
	sl->setWordList(wordList);
	wordList.clear();
	connect(sl->searchBtn, SIGNAL(clicked()), this, SLOT(searchItem()));
	view->view()->viewport()->update();

	//重新绘制一次
	this->setFocus();
}

void MainWidget::resizeEvent(QResizeEvent *event)
{
	mylegend->move(width() - 650, height() - 130);
	compass->move(width() - 130, 30);
	sl->move(30, 30);
}

//
void MainWidget::showDetails()
{
	if (scene->selectedItems().empty() == true)return;
	//获取当前被选中的点，查找数据库中关于它的信息，然后以一个layer显示出来
	StationPoint *pItem = qgraphicsitem_cast<StationPoint *>(scene->selectedItems().at(0));
	if (pItem &&pItem->pointType() == StationPoint::Station)
	{
		QString stationInfo = pItem->xb + "," + pItem->station;
		wchar_t *data = new wchar_t[stationInfo.length() + 1];
		stationInfo.toWCharArray(data);
		data[stationInfo.length()] = '\0';
		COPYDATASTRUCT cdate;
		cdate.cbData = stationInfo.length()+1;
		cdate.dwData = 7003;
		cdate.lpData = data;
		qDebug() << data;
		::SendMessageA(pHandle, WM_COPYDATA, 0, (LPARAM)&cdate);	
	}
	if (pItem &&pItem->pointType() == StationPoint::PathPointWithImg)
	{
		QString ImgPointInfo = pItem->pguid;
		wchar_t *data = new wchar_t[ImgPointInfo.length() + 1];
		ImgPointInfo.toWCharArray(data);
		data[ImgPointInfo.length()] = '\0';
		COPYDATASTRUCT cdate;
		cdate.cbData = ImgPointInfo.length() + 1;
		cdate.dwData = 7005;
		cdate.lpData = data;
		qDebug() << data;
		::SendMessageA(pHandle, WM_COPYDATA, 0, (LPARAM)&cdate);
	}
}

void MainWidget::showHumanDetails()
{
	//发送人员定位信息
	HumanPoint *selectedHuman = qgraphicsitem_cast<HumanPoint *>(scene->selectedItems().at(0));
	QString senderID = selectedHuman->id;
	wchar_t *data = new wchar_t[senderID.length() + 1];
	senderID.toWCharArray(data);
	data[senderID.length()] = '\0';
	COPYDATASTRUCT cdate;
	cdate.cbData = senderID.length() + 1;
	cdate.dwData = 7004;
	cdate.lpData = data;
	qDebug() << data;
	::SendMessageA(pHandle, WM_COPYDATA, 0, (LPARAM)&cdate);
}

void MainWidget::PreviewLostFocus(PreView *item)
{
	item->deleteLater();
}


void MainWidget::createActions()
{
    showDetailsAction = new QAction(tr("Coordinate"),this);
    showDetailsAction->setShortcut(tr("Ctrl+S"));
    showDetailsAction->setStatusTip(tr("Show it's coordinate"));
    connect(showDetailsAction,SIGNAL(triggered()),this,SLOT(showDetails()));
}

//创建菜单
void MainWidget::createMenus()
{
    myItemMenu = new QMenu(tr("&Item"),this);
    myItemMenu->addAction(showDetailsAction);
    myItemMenu->addSeparator();
}


QPointF MainWidget::maptoscene(QPointF p)
{
    qreal jwChange = 0.02;
    QPointF scenePoint;
    qreal jd = p.x();
    qreal wd = p.y();
    //Scene的宽和高
    qreal w =scene->sceneRect().width();
    qreal h =scene->sceneRect().height();

    qreal jdmin = jmin-jwChange;
    qreal wdmin = wmin-jwChange;
    qreal jdmax = jmax+jwChange;
    qreal wdmax = wmax+jwChange;

    //转换
    qreal sx = (jd-jdmin)/abs((jdmax-jdmin)/w);
    qreal sy = -(wd-wdmax)/abs((wdmax-wdmin)/h);
    scenePoint.setX(sx);
    scenePoint.setY(sy);
    return scenePoint;
}
void MainWidget::addItemLine(StationPoint *start, StationPoint *end, LineItem::LineType linetype, QString xb)
{
    //先把第一次结果保存下来
    LineItem *line = new LineItem(start,end,linetype);
    line->setColor(myLineColor);
    QString linename = start->station+"--"+end->station;
    mylines[linename]=line;
    line->LineName = linename;
    line->xbName = xb;
    //然后遍历出LineName的所有信号机
    for(int i=0;i<smPoints.length();i++)
    {
        if(smPoints.at(i).station==linename)
        {
            QPointF smPoint(smPoints.at(i).jd,smPoints.at(i).wd);
            smPoint=maptoscene(smPoint);
            signalMachinePoint smp(smPoints.at(i).devicename,smPoint);
            line->signalMachinePoints.append(smp);
        }
    }
    //start->addLine(line);
    //end->addLine(line);
    //这里连不上是因为lineitem中的addline代码没写好
    line->setZValue(-1000.0);
    scene->addItem(line);
    line->updatePosition();
    line->createSignalMachinePainterPath();
}
void MainWidget::addName(StationPoint *centerItem)
{
    //用QPainterPath找items（画扇形）
    QPainterPath *pCircle;
    //文字宽度
    qreal textsize = 10;

    QString pname = centerItem->station;
    TextItem *ptextitem = new TextItem();
    ptextitem->setPlainText(pname);
    qreal pStep = 90;
    qreal pLength = ptextitem->boundingRect().width();
    //半径
    const qreal r=pLength;
    QRectF Nrect(0,0,r*2,r*2);
    Nrect.translate(centerItem->pos().x()-r,centerItem->pos().y()-r);
    QHash<int,QPointF>pPoint;
    for(int i = -45; i < 360;i+=pStep )
    {
        pCircle = new QPainterPath();
        pCircle->moveTo(centerItem->pos().x(),centerItem->pos().y());
        //qreal pArc = ((pLength>(2*r))?qAsin(1):(qAsin(pLength/(2*r)))*180/Pi);
        pCircle->arcTo(Nrect,i,pStep);
        pCircle->lineTo(centerItem->pos().x(),centerItem->pos().y());
        //addPath(*pCircle,QPen(Qt::black));
        QList<QGraphicsItem *>tempItems=scene->items(*pCircle);
        delete pCircle;
        //移动的幅度
        qreal qGap = 2;
        int iCount = 0;
        foreach (QGraphicsItem *i, tempItems) {
            if(i->type()==item->type()||i->type()==ptextitem->type())iCount++;
        }
        if(iCount<=1)
        {
            //就可以在这里加文字
            //先设置文字的尺寸大小
            QFont font = ptextitem->font();
            font.setPointSize(10);
            ptextitem->setFont(font);

            switch (i) {
            case 135:
                //判断一下，如果贴墙的话就换
                if(byTheSide(QPointF(centerItem->pos().x(),centerItem->pos().y()))!=3)
                {
                    scene->addItem(ptextitem);
                    ptextitem->setPos(centerItem->pos().x()-qGap,centerItem->pos().y());
                    break;
                }
            case -45:
                if(byTheSide(QPointF(centerItem->pos().x(),centerItem->pos().y()))!=1)
                {
                    scene->addItem(ptextitem);
                    //判断一下，如果贴墙的话就换
                    ptextitem->setPos(centerItem->pos().x()+qGap,centerItem->pos().y());
                    break;
                }
            case 45 :
                if(byTheSide(QPointF(centerItem->pos().x(),centerItem->pos().y()))!=2)
                {
                    scene->addItem(ptextitem);
                    ptextitem->setTextWidth(textsize);
                    ptextitem->setPos(centerItem->pos().x(),centerItem->pos().y()+qGap);
                    break;
                }
            case 225:
                if(byTheSide(QPointF(centerItem->pos().x(),centerItem->pos().y()))!=4)
                {
                    scene->addItem(ptextitem);
                    ptextitem->setTextWidth(textsize);
                    ptextitem->setPos(centerItem->pos().x(),centerItem->pos().y()-qGap);
                    break;
                }
            default:
                break;
            }
            //将item在中垂线上移动
            return;
        }
        else
        {
            switch (i) {
            case 135:
                pPoint[iCount]=QPointF(centerItem->pos().x()-r/2,centerItem->pos().y());
                break;
            case -45:
                pPoint[iCount]=QPointF(centerItem->pos().x()+r/2,centerItem->pos().y());
                break;
            case 45:
                pPoint[iCount]=QPointF(centerItem->pos().x(),centerItem->pos().y()+r/2);
                break;
            case 225:
                pPoint[iCount]=QPointF(centerItem->pos().x(),centerItem->pos().y()-r/2);
                break;
            default:
                break;
            }
        }
        //还没有返回的话
        if(i==225)
        {
            for(int i = 2 ;i<100 ;i++)
            {
                if(pPoint.contains(i))
                {
                    scene->addItem(ptextitem);
                    ptextitem->setTextWidth(textsize);
                    ptextitem->setPos(pPoint[i]);
                    return;
                }
            }
        }
    }
}
int MainWidget::byTheSide(QPointF checkPoint)
{
    qreal size = 20;
    if(checkPoint.x()>scene->sceneRect().width()-size)
        return 1;
    if(checkPoint.y()<size)
        return 2;
    if(checkPoint.x()<size)
        return 3;
    if(checkPoint.y()>scene->sceneRect().height()-size)
        return 4;
    else
        return 0;
}
void MainWidget::iniRoadPath()
{
    QString sql("select distinct ROUTENAME from ROUTES");
    QSqlQuery query(m_pDB->GetDatabase());
    if(!query.exec(sql))
    {
        qDebug()<<query.lastError();
        return;
    }

    QList<QString>pathNameList;
    while(query.next())
    {
        //先保存有几个路线名
        pathNameList.append(query.value(0).toString());
    }
    //然后再根据路径名查询每一条路径，再绘制
    //关于内存管理和线程的知识需要充电！
    //QHash<QString,QPainterPath>pathList;
    QPainterPath *pPath;
    for(int i =0 ; i <pathNameList.count();i++)
    {
        QString routeName = pathNameList.at(i);
        sql = "select * from ROUTES where ROUTENAME = '"+routeName+"' order by PST";
        if(!query.exec(sql))
        {
            qDebug()<<query.lastError();
            return;
        }
        int index = 0;
        pPath = new QPainterPath;
        while(query.next())
        {
            //存入内存中
            qreal pJD = query.value("JD").toReal();
            qreal pWD = query.value("WD").toReal();
            QString picName = query.value("PICNAME").toString();
            //直接画路径
            if(index==0)
                pPath->moveTo(maptoscene(QPointF(pJD,pWD)));
            else
                pPath->lineTo(maptoscene(QPointF(pJD,pWD)));
            if(picName!="null")
            {
                item = new StationPoint(StationPoint::PathPointWithImg,myItemMenu);
                scene->addItem(item);
                item->setPos(maptoscene(QPointF(pJD,pWD)));
                item->setZValue(2);
				item->pguid = query.value("PGUID").toString();
            }
            index++;
        }
        myLineColor = QColor(189,179,87,255);

		PolyLine *pl = new PolyLine(*pPath);
		scene->addItem(pl);
        QPolygonF polygonf;
        //存进来，放进来，在toline类中在进行处理吧，这个类我只想安静的画画
        polygonf = pPath->toFillPolygon();
        YelloPaths[routeName]=polygonf;
        delete pPath;
    }
}
void MainWidget::iniStationPoint()
{
    QHash<QString,StationPoint*>::const_iterator i = pointItems.constBegin();
    while( i != pointItems.constEnd())
    {
        item = i.value();
        qreal jd = i.value()->jd;
        qreal wd = i.value()->wd;
        ++i;
        //开始画点
        QPointF point(jd,wd);
        point = maptoscene(point);
        scene->addItem(item);
        item->setPos(point);
        item->setZValue(2);
    }
}
void MainWidget::iniStationLine()
{
    m_pDB->GetInstance();
    QString strPath(DB_GxDataPath);
    if(NULL == m_pDB)
    {
        return;
    }
    if(!m_pDB->ConnectAccessDB(strPath,"","zbxh2012base518"))
    {
        return;
    }
    QString sql = QString::fromLocal8Bit("select * from MangeUnit where NameStart<>''");
    QSqlQuery query(m_pDB->GetDatabase());
    if(!query.exec(sql))
    {
        return;
    }
    //设置颜色
    myLineColor = Qt::black;
    while(query.next())
    {
        //items的根据DEVICENAME检索
        QString NameStart = query.value("NameStart").toString();
        QString NameEnd = query.value("NameEnd").toString();
        QString xb = query.value("Xb").toString();
        if(pointItems.contains(NameStart)&&pointItems.contains(NameEnd))
            addItemLine(pointItems.value(NameStart),pointItems.value(NameEnd),LineItem::StationLine,xb);
    }
}
void MainWidget::iniStationName()
{
    foreach (StationPoint *pitem, pointItems) {
        addName(pitem);
    }
}
void MainWidget::iniTextName()
{
    QGraphicsTextItem * item;
    for(int i = 0 ;i<1000;i++)
    {
        QString temp = "22"+QString::number(i);
        item = new QGraphicsTextItem(temp);
        QFont font;
        scene->addItem(item);
        item->setPos(i*1.1,i*1.1);
    }
}

bool MainWidget::ConnectDB()
{
    QString strPath(DB_PersoninfoPath);
    if(NULL == m_pDB)
    {
        return false;
    }
    if(!m_pDB->ConnectAccessDB(strPath,"",""))
    {
        return false;
    }
    return true;
}
void MainWidget::initData()
{
    //解决中文路径问题
    //QString sql = QString::fromLocal8Bit("select * from DEVICE t1 where not exists(select * from DEVICE where DEVICENAME=t1.DEVICENAME and S_UDTIME>t1.S_UDTIME) and DEVICETYPE in('信号楼','工区:信号楼')");
    QString sql=QString::fromLocal8Bit("select device.* from device inner join (select max(S_UDTIME),max(PGUID) as MGUID from device  group by STATION,XB,PT_DWNAME,DEVICENAME ) t on t.MGUID=device.PGUID  where DEVICETYPE like '%信号楼%'");
    //sql = code->fromUnicode(sql);
    //从数据库中读取数据
    //这样会卡，应该只读一次数据，然后放到QHash里面每次重绘就直接遍历哈希表
    QSqlQuery query(m_pDB->GetDatabase());
    if(!query.exec(sql))
    {
        return;
    }
    myItemType = StationPoint::Station;
	int i = 1;
    while(query.next())
    {
        //通过一个数据结构保存
        item = new StationPoint(myItemType,myItemMenu);
        item->locator = query.value("LOCATOR").toString();
        item->station = query.value("STATION").toString();
        item->devicename = query.value("DEVICENAME").toString();

		item->textPos = i;
		if (i == 1)
			i = 2;
		else if (i == 2)
			i = 1;

        item->devicetype = query.value("DEVICETYPE").toString();
        item->xb = query.value("XB").toString();
        item->dwname = query.value("PT_DWNAME").toString();
        item->jd = query.value("JD").toDouble();
        item->wd = query.value("WD").toDouble();
        item->id = query.value("ID").toInt();
        pointItems[item->station]=item;
		wordList << item->station;
    }
    //在代码中过滤掉STATIONS表中的数据吧
    sql = QString::fromLocal8Bit("select * from STATIONS");
    if(!query.exec(sql))
    {
        qDebug()<<query.lastError();
        return;
    }

    while(query.next())
    {
        QString s_station = query.value("STATION").toString();
        if(pointItems.contains(s_station))continue;
        item = new StationPoint(myItemType,myItemMenu);
        item->locator = query.value("LOCATOR").toString();
        item->station = query.value("STATION").toString();
        //item->devicename = query.value("DEVICENAME").toString();
		item->textPos = i;
		if (i == 1)
			i = 2;
		else if (i == 2)
			i = 1;
        //item->devicetype = query.value("DEVICETYPE").toString();
        item->xb = query.value("XB").toString();
        item->dwname = query.value("PT_DWNAME").toString();
        item->jd = query.value("JD").toDouble();
        item->wd = query.value("WD").toDouble();
        item->id = query.value("ID").toInt();
        pointItems[item->station]=item;
		wordList << item->station;
    }



    //先找出左上和右下的坐标
    sql = QString::fromLocal8Bit("select max(JD),min(JD),max(WD),min(WD) from (select JD,WD from DEVICE where DEVICETYPE in('工区:信号楼','信号楼') union select JD,WD from ROUTES union select JD,WD from STATIONS)");
    if(query.exec(sql))
    {
        while (query.next()) {
            jmax=query.value(0).toReal();
            jmin=query.value(1).toReal();
            wmax=query.value(2).toReal();
            wmin=query.value(3).toReal();
        }
    }

    //保存信号机的信息
    sql = QString::fromLocal8Bit("select * from DEVICE  where S_UDTime in (select max(S_UDTIME) from DEVICE where DEVICETYPE='信号机' group by DEVICENAME,STATION,MAPNAME,XB,PT_DWNAME)"
                                 " and DEVICETYPE='信号机'");
    if(query.exec(sql))
    {
        QString _station;
        QString _mapname;
        QString _devicename;
        qreal _jd;
        qreal _wd;
        QString _xb;
        QString _dwname;
        while(query.next())
        {
            _station = query.value("STATION").toString();
            if(!_station.contains("-"))continue;
            _mapname = query.value("MAPNAME").toString();
            _devicename = query.value("DEVICENAME").toString();
            _jd = query.value("JD").toReal();
            _wd = query.value("WD").toReal();
            _xb = query.value("XB").toString();
            _dwname = query.value("PT_DWNAME").toString();
            SignalMachinePointInfo temp(_station,_mapname,_devicename,
                                        _jd,_wd,_xb,_dwname);
            smPoints.append(temp);
        }
    }
}
/*search*/
void MainWidget::searchItem()
{
	QString stationName = sl->text();
	if (stationName == "")return;
	view->view()->fitInView(view->view()->sceneRect(), Qt::KeepAspectRatio);
	if (pointItems.contains(stationName))
	{
		qreal sidel = 500;
		QPointF m_pos = pointItems[stationName]->pos();
		pointItems[stationName]->focusItem();
		view->view()->fitInView(QRect(m_pos.x() - sidel / 2, m_pos.y() - sidel / 2, sidel, sidel), Qt::KeepAspectRatio);
	}
}
//拦截回车
bool MainWidget::eventFilter(QObject *watched, QEvent *event)
{
	if (watched == sl)
	{
		if (event->type() == QEvent::KeyPress)
		{
			QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
			if (keyEvent->key()+1  == Qt::Key_Enter)
			{
				emit sl->searchBtn->click();
				return true;
			}
			else
				return QWidget::eventFilter(watched, event);
		}
		else
		{
			return QWidget::eventFilter(watched, event);
		}
	}
	return QWidget::eventFilter(watched, event);
}

///////////////////////////////////////////////////////////////

void MainWidget::drawDynamicInfo(QString xml)
{
    MyXml myxml(xml);
    QString mesgstate = myxml.getMesgState();
    //人员GPS定位
    if(mesgstate == myxml.MesgState.value(12) || mesgstate == myxml.MesgState.value(13) ||
            mesgstate == myxml.MesgState.value(14))
    {
        HumanPoint *human = myxml.getHumanPoint();
		if (humans.contains(human->senderName))
		{
			emit cleanHumanPoint(human->senderName);
		}
		connect(human, SIGNAL(disappear(QString)), this, SLOT(cleanHumanPoint(QString)));
		connect(human, SIGNAL(onClicked()), this, SLOT(showHumanDetails()));
		humans[human->senderName] = human;
        DoServiceInfoGPSInfo(human);
    }
    //应急指挥报警
    if(mesgstate == myxml.MesgState.value(16))
    {
		//两种报警同种信号
        QStringList xbandstation=myxml.getAlarmXbAndStation().split(",");
        QString m_xb = xbandstation.at(0);
        QString m_station = xbandstation.at(1);

		DoErrorAlarm(m_xb,m_station);

    }
	//取消报警
	if (mesgstate == myxml.MesgState.value(15))
	{
		//station or stationline
		if (myxml.stationname.contains("--"))
		{
			QStringList stationnameList = myxml.stationname.split("--");
			if (mylines.contains(stationnameList.at(1)+"--"+stationnameList.at(0)))
			{
				mylines.value(stationnameList.at(1) + "--" + stationnameList.at(0))->alarmClose();
			}
			else if (mylines.contains(myxml.stationname))
			{
				mylines.value(myxml.stationname)->alarmClose();
			}
		}
		else if (pointItems.contains(myxml.stationname))
		{
			pointItems.value(myxml.stationname)->setAlarm(false);
		}
	}
}
//************************所有的信号处理函数*************************//
void MainWidget::DoServiceInfoGPSInfo(HumanPoint *human)
{
    //闪烁的人点，实时接收数据处理坐标，放在线上
    scene->addItem(human);
    qreal jd = human->jd;
    qreal wd = human->wd;
    QString fromstop = human->fromStop;
    QPointF HumanPos = maptoscene(QPointF(jd,wd));
    HumanPos = toline->isPointOnPloylineTest_02(HumanPos,YelloPaths.value(fromstop));
    human->setPos(HumanPos-QPointF(25,25));
    human->setZValue(2);
	scene->update();
}
void MainWidget::DoErrorAlarm(QString linename,QString stationname)
{
    //找到这条区间,然后设置ifAlarm为true
	if (stationname.contains("--"))
	{
		QStringList stationnameList = stationname.split("--");
		if(mylines.contains(stationname))
		{
			if(mylines.value(stationname)->xbName==linename)
				mylines.value(stationname)->alarmOpen();
		}
		else if (!stationnameList.isEmpty()&&mylines.contains(stationnameList.at(1) + "--"
			+ stationnameList.at(0)))
		{
			stationname = stationnameList.at(1) + "--" + stationnameList.at(0);
			if (mylines.value(stationname)->xbName == linename)
				mylines.value(stationname)->alarmOpen();
		}
	}
    //这个是报警的点
    else if(pointItems.contains(stationname))
    {
        StationPoint *temppoint = pointItems.value(stationname);
        if(temppoint->xb==linename)
        {
			temppoint->setAlarm(true);
			//这个不可或缺
			temppoint->update();
        }
    }
	scene->update();
}
void MainWidget::cleanHumanPoint(QString humanName)
{
	if (humans.contains(humanName))
	{
		QHash<QString, HumanPoint*>::const_iterator i = humans.find(humanName);
		delete i.value();
		humans.erase(i);
		scene->update();
	}
}