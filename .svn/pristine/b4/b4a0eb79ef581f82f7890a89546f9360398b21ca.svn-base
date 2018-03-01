#include "myxml.h"
#include <QMessageBox>
MyXml::MyXml(QString xmlstring)
{
    xmlString = xmlstring;
    ifconn=iniXml();
    iniMesgType();
    iniMesgState();
    readXml();
    dealWithMesginfo();
    qDebug()<<parseMesg()<<mesgtype<<mesgstate<<fromstop<<sendername;
}
int MyXml::readXml()
{
    if(ifconn!=1)return -1;
    //读取根节点
    QDomElement root = doc.documentElement();
    QDomNode node_head = root.firstChild();//读取消息头节点
    QDomNode node_body = node_head.nextSibling(); //读取消息体节点
    QDomNodeList nodelist_head = node_head.childNodes();
    QDomNodeList nodelist_body = node_body.childNodes();
    if(!nodelist_head.isEmpty())
    for(int i = 0 ;i<nodelist_head.count();i++)     //先是消息头
    {
        QDomNode tempnode = nodelist_head.at(i);
        if(tempnode.nodeName()=="MsgType")
        {
            mesgtype = MesgType.value(tempnode.toElement().text().toInt());
        }
        else if(tempnode.nodeName()=="MsgState")
        {
            mesgstate_int = tempnode.toElement().text().toInt();
        }
        else if(tempnode.nodeName()=="SenderName")
        {
            sendername = tempnode.toElement().text();
        }
		else if (tempnode.nodeName() == "SenderID")
		{
			senderID = tempnode.toElement().text();
		}
    }
    //处理得到mesginfo

    //再是消息体
    if(!nodelist_body.isEmpty())
    for(int i = 0 ; i<nodelist_body.count();i++)
    {
        QDomNode tempnode = nodelist_body.at(i);
        //不同的消息需要解析的东西不一样
        //先不管，都判断
        if(tempnode.nodeName()=="FromStop")
        {
            //一个头一个尾，要分开解析
            fromstop = tempnode.toElement().text();
        }
        else if(tempnode.nodeName()=="JD")
        {
            jd = tempnode.toElement().text().toDouble();
        }
        else if(tempnode.nodeName()=="WD")
        {
            wd = tempnode.toElement().text().toDouble();
        }
        else if(tempnode.nodeName()=="LineName")
        {
            linename = tempnode.toElement().text();
        }
        else if(tempnode.nodeName()=="StationName")
        {
            stationname = tempnode.toElement().text();
        }
    }


    return 0;
}
QString MyXml::getMesgState()
{
    return mesgstate;
}

int MyXml::iniXml()
{
    if(!doc.setContent(xmlString))
    {
        QMessageBox::information(NULL, QString("title"), QString("xml parse error!"));
        return -1;
    }
	return 1;
}
HumanPoint *MyXml::getHumanPoint()
{
	humanpoint = new HumanPoint(sendername);
    humanpoint->fromStop = fromstop;
    humanpoint->jd = jd;
    humanpoint->wd = wd;
	humanpoint->id = senderID;
    return humanpoint;
}
QString MyXml::parseMesg()
{
    QString IntMesgType = mesgtype;
    return IntMesgType;
}
void MyXml::dealWithMesginfo()
{
    //读取ini文件并进行解析
    QSettings *configIniRead = new QSettings("XmlData.ini",QSettings::IniFormat);
    //将读取到的ini文件保存在QString中，先取值，然后通过toString()函数转换成QString类型
    QString temp;
    temp.setNum(mesgstate_int);
    temp="/"+mesgtype+"/"+temp;
    mesgstate = configIniRead->value(temp).toString();
}
QString MyXml::getAlarmXbAndStation()
{
    return linename+","+stationname;
}
