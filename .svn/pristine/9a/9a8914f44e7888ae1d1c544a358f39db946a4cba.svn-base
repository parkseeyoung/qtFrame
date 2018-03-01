#include "preview.h"
#include <QtWidgets>
PreView::PreView(StationPoint *item, PreViewType previewType)
{
    setMinimumSize(50,50);
    setWindowFlags(Qt::Drawer);
    setWindowTitle(QString(item->station));
    if(previewType == StationInfoType)
        createStatinoInfoView(item);
    else if(previewType == ImgType)
        createImgView(item);
    //pView->move(pView->mapFromParent(item->pos().toPoint()));
    //设置是否靠边了

    move(QCursor::pos().x()+5,QCursor::pos().y()+5);
    //设置焦点
    setFocus();
    show();
}
void PreView::focusOutEvent(QFocusEvent *event)
{
    emit lostFocus(this);
    QGraphicsView::focusOutEvent(event);
}
void PreView::createImgView(StationPoint *item)
{
    QString temp;
    //PicName

}
void PreView::createStatinoInfoView(StationPoint *item)
{
    QString temp;

    //id
    QLabel *pIdLabel = new QLabel();
    QLineEdit *pIdEdit = new QLineEdit();
    pIdLabel->setText("ID:");
    pIdEdit->setEnabled(false);
    pIdEdit->setText(temp.setNum(item->id));

    //station
    QLabel *pStationLabel = new QLabel();
    QLineEdit *pStationEdit = new QLineEdit();
    pStationLabel->setText("Station");
    pStationEdit->setEnabled(false);
    pStationEdit->setText(item->station);

    //locator
    QLabel *pLocatorLabel = new QLabel();
    QLineEdit *pLocatorEdit = new QLineEdit();
    pLocatorLabel->setText("Locator:");
    pLocatorEdit->setEnabled(false);
    pLocatorEdit->setText(item->locator);

    //Devicename
    QLabel *pDevicenameLabel = new QLabel();
    QLineEdit *pDevicenameEdit = new QLineEdit;
    pDevicenameLabel->setText("Devicename:");
    pDevicenameEdit->setEnabled(false);
    pDevicenameEdit->setText(item->devicename);

    //Devicetype
    QLabel *pDevicetypeLabel = new QLabel();
    QLineEdit *pDevicetypeEdit = new QLineEdit;
    pDevicetypeLabel->setText("Devicetype:");
    pDevicetypeEdit->setEnabled(false);
    pDevicetypeEdit->setText(item->devicetype);

    //xb
    QLabel *pXbLabel = new QLabel();
    QLineEdit *pXbEdit = new QLineEdit;
    pXbLabel->setText("Xb:");
    pXbEdit->setEnabled(false);
    pXbEdit->setText(item->xb);

    //Dwname
    QLabel *pDwnameLabel = new QLabel();
    QLineEdit *pDwnameEdit = new QLineEdit;
    pDwnameLabel->setText("Dwname:");
    pDwnameEdit->setEnabled(false);
    pDwnameEdit->setText(item->dwname);

// 添加 widget
    QGraphicsScene *pScene = new QGraphicsScene();
    //id
    QGraphicsProxyWidget *pIdLabelWidget = pScene->addWidget(pIdLabel);
    QGraphicsProxyWidget *pIdEditWidget = pScene->addWidget(pIdEdit);
    //station
    QGraphicsProxyWidget *pStationLabelWidget = pScene->addWidget(pStationLabel);
    QGraphicsProxyWidget *pStationEditWidget = pScene->addWidget(pStationEdit);
    //locator
    QGraphicsProxyWidget *pLocatorLabelWidget = pScene->addWidget(pLocatorLabel);
    QGraphicsProxyWidget *pLocatorEditWidget = pScene->addWidget(pLocatorEdit);
    //Devicename
    QGraphicsProxyWidget *pDevicenameLabelWidget = pScene->addWidget(pDevicenameLabel);
    QGraphicsProxyWidget *pDevicenameEditWidget = pScene->addWidget(pDevicenameEdit);
    //Devicetype
    QGraphicsProxyWidget *pDevicetypeLabelWidget = pScene->addWidget(pDevicetypeLabel);
    QGraphicsProxyWidget *pDevicetypeEditWidget = pScene->addWidget(pDevicetypeEdit);
    //Xb
    QGraphicsProxyWidget *pXbLabelWidget = pScene->addWidget(pXbLabel);
    QGraphicsProxyWidget *pXbEditWidget = pScene->addWidget(pXbEdit);
    //Dwname
    QGraphicsProxyWidget *pDwnameLabelWidget = pScene->addWidget(pDwnameLabel);
    QGraphicsProxyWidget *pDwnameEditWidget = pScene->addWidget(pDwnameEdit);

// 添加至网格布局中
    QGraphicsGridLayout *pLayout = new QGraphicsGridLayout();
    //id
    pLayout->addItem(pIdLabelWidget,0,0);
    pLayout->addItem(pIdEditWidget,0,1);
    //station
    pLayout->addItem(pStationLabelWidget,1,0);
    pLayout->addItem(pStationEditWidget,1,1);
    //locator
    pLayout->addItem(pLocatorLabelWidget,2,0);
    pLayout->addItem(pLocatorEditWidget,2,1);
    //Devicename
    pLayout->addItem(pDevicenameLabelWidget,3,0);
    pLayout->addItem(pDevicenameEditWidget,3,1);
    //Devicetype
    pLayout->addItem(pDevicetypeLabelWidget,4,0);
    pLayout->addItem(pDevicetypeEditWidget,4,1);
    //Xb
    pLayout->addItem(pXbLabelWidget,5,0);
    pLayout->addItem(pXbEditWidget,5,1);
    //Dwname
    pLayout->addItem(pDwnameLabelWidget,6,0);
    pLayout->addItem(pDwnameEditWidget,6,1);

//整体布局
    QGraphicsWidget *pWidget = new QGraphicsWidget();
    pWidget->setLayout(pLayout);
// 将 item 添加至场景中
    pScene->addItem(pWidget);
    pScene->setSceneRect(0,0,240,200);
    setScene(pScene);
    //fitInView(sceneRect(),Qt::KeepAspectRatio);
}
