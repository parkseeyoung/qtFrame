#ifndef PAINTFRAME_H
#define PAINTFRAME_H

#include <QtWidgets/QWidget>
#include <ActiveQt/QAxBindable>
#include "frame\mainwidget.h"
#include "qt_windows.h"

class PaintFrame : public QWidget, public QAxBindable
{
	Q_OBJECT
	Q_CLASSINFO("Version", "1.0")
	Q_CLASSINFO("ClassID", "{CD70F4F5-05C2-40C2-B611-5B86EF5BDB3E}")
	Q_CLASSINFO("InterfaceID", "{CB8695B2-1B59-4A7E-AD07-527A4729D72B}")
	Q_CLASSINFO("EventsID", "{4B52CD3B-E7B9-448A-8989-17DC85AA06F6}")
	Q_CLASSINFO("Insertable", "yes")
	Q_CLASSINFO("ToSuperClass", "PaintFrame")
public:
	PaintFrame(QWidget *parent = 0);

private:
	MainWidget * mw;
	bool nativeEvent(const QByteArray &eventType, void *message, long *result);
	HWND parentHandle;
};

#endif // PAINTFRAME_H
