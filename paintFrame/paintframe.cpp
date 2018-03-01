#include "paintframe.h"

#include <ActiveQt/QAxFactory>
#include <qgridlayout.h>

PaintFrame::PaintFrame(QWidget *parent)
	: QWidget(parent)
{
	
}
bool PaintFrame::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
	Q_UNUSED(eventType);
	MSG *msg = reinterpret_cast<MSG*>(message);
	//初始化
	if (msg->message == (7001))
	{
		wchar_t *bothStr_ = (wchar_t*)msg->lParam;
		QString bothStr = QString::fromWCharArray(bothStr_);

		QString GxDataPath = bothStr.left(bothStr.indexOf(","));


		QString PersonInfoPath = bothStr.right(bothStr.length() - 1 - bothStr.indexOf(","));

		mw = new MainWidget(this);
		QLayout *exist_layout = this->layout();
		if (exist_layout)
		{
			delete exist_layout;
		}
		QGridLayout *layout = new QGridLayout;
		layout->addWidget(mw, 0, 0);
		layout->setContentsMargins(0, 0, 0, 0);
		this->setLayout(layout);
		mw->pHandle = parentHandle;
		mw->iniAll(PersonInfoPath, GxDataPath);
	}
	//7006句柄
	if (msg->message == (7006))
	{
		char* handle = (char*)msg->lParam;
		int handle_int = atoi(handle);
		parentHandle = (HWND)handle_int;
	}
	//7002实事消息
	if (msg->message == (7002))
	{
		wchar_t* xmlMsg = (wchar_t*)msg->lParam;
		QString xml = QString::fromWCharArray(xmlMsg);
		mw->drawDynamicInfo(xml);
	}
	return false;
}

QAXFACTORY_DEFAULT(PaintFrame,
	   "{CA1B8154-64AA-4A2A-B222-4F57117CA04C}",
	   "{9D7D1AAB-FDAA-4C4B-AFBE-49CFA7D2F809}",
	   "{713BE417-3E13-4B09-B5B0-DFAFCFA8A3F9}",
	   "{F294DC09-C77D-42EC-9505-E45CFE8A5363}",
	   "{1B0FF959-76EF-45EE-A20A-D0DDFA8127A7}")
