#ifndef MYXML_H
#define MYXML_H
#include <QDebug>
#include <QtXml/QtXml>
#include <QtXml/QDomDocument>
#include <QtXml/QDomText>

#include <QtCore/QCoreApplication>
#include <QFile>
#include <QSettings>
#include "humanpoint.h"

class MyXml
{
public:
    //直接做一个数组算了，其实我也不知道枚举有啥用
    QHash<int,QString>MesgType;
    void iniMesgType(){
        MesgType[1]="AccidentDetails";      //故障信息
        MesgType[2]="TroubleshootingInformation";       //故障处理信息2
        MesgType[3]="ReturnValueMesg";      //返回值消息3
        MesgType[4]="ServiceInfo";          //服务信息4
        MesgType[5]="ManualCommand";        //人工指挥5
        MesgType[6]="CoreData";             //关键数据6
        MesgType[7]="SkylightPoint";        //天窗点7
        MesgType[8]="PhoneFailureReported"; //手机故障上报8
        MesgType[9]="WifiCommunication";    //WIFI通信9
        MesgType[10]="EmergencyCommand";    //应急指挥10
    }

    //消息枚举
    QHash<int,QString> MesgState;
    void iniMesgState(){
        MesgState[1]="AccidentDetailsOccur";
        MesgState[2]="AccidentDetailsDealingWith";
        MesgState[3]="AccidentDetailsDealed";
        MesgState[4]="AccidentDetailsDispatchAlarmNotification";
        MesgState[5]="AccidentDetailsImageInfo";
        MesgState[6]="AccidentDetailsVideoInfo";


        MesgState[7]="TroubleshootingInformationDealing";
        MesgState[8]="TroubleshootingInformationDealed";
        MesgState[9]="TroubleshootingInformationPhoneChangeAlarm";

        MesgState[10]="ReturnValueMesgDealing";
        MesgState[11]="ReturnValueMesgCauseOfIssue";

        MesgState[12]="ServiceInfoGPSInfo";
        MesgState[13]="ServiceInfoNavigation";
        MesgState[14]="ServiceInfoWifiInfo";

        MesgState[15]="ManualCommandEnd";

        MesgState[16]="EmergencyCommandAlarmNotification";
    }

public:
    MyXml(QString xmlstring);
    int readXml();
    QString xmlString;
    //解析mesgtype
    QString parseMesg();
    void dealWithMesginfo();
    //最后的类型
    QString getMesgState();
private:

    QDomDocument doc;
    //初始化
    int iniXml();
    int ifconn;
    QString mesgtype;
    int mesgstate_int;
    QString mesgstate;
    //主要的判断函数
    //这个应该写在scene中！
	HumanPoint *humanpoint;
public:
//消息参数
    //GPS消息
    QString fromstop;
    QString sendername;
    qreal jd;
    qreal wd;

    //Alarm信息
    QString linename;
    QString stationname;


//返回消息
    //人
	QString senderID;
public:
    HumanPoint *getHumanPoint();
    //返回报警线路,线别和站场，防止名称一样，唯一性确定。
    QString getAlarmXbAndStation();
};

#endif // MYXML_H
