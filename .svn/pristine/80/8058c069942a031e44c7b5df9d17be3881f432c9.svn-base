#ifndef PREVIEW_H
#define PREVIEW_H
#include "stationpoint.h"
#include <QGraphicsView>
class PreView : public QGraphicsView
{
    Q_OBJECT
public:
    enum PreViewType {ImgType,StationInfoType};
    PreView(StationPoint *item, PreViewType previewType);
    void focusOutEvent(QFocusEvent *event);
protected:
    //如果点击的GreenImage就显示图片
    void createImgView(StationPoint *item);
    //创建显示站场信息的视图
    void createStatinoInfoView(StationPoint *item);
signals:
    void lostFocus(PreView *item);
};

#endif // PREVIEW_H
