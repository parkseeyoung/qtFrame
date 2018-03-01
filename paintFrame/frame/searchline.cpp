#include "searchline.h"
#include <QCompleter>

searchLine::searchLine(QWidget *parent)
    :QLineEdit(parent)
{
    QHBoxLayout *mainLayout = new QHBoxLayout;
    searchBtn = new QPushButton;
    searchBtn->setFixedSize(18,18);
    searchBtn->setCursor(Qt::PointingHandCursor);
    searchBtn->setToolTip(QString::fromLocal8Bit("搜索"));
    searchBtn->setStyleSheet("QPushButton{border-image:url(:/frame/img/search-icon.png);"
                             "background:transparent;cursor:pointer;}");
    setPlaceholderText(QString::fromLocal8Bit("搜索"));
    mainLayout->addWidget(searchBtn);
    mainLayout->addStretch();
    //mainLayout->setContentsMargins(8,8,8,8);
    mainLayout->setContentsMargins(8,0,0,0);
    setTextMargins(13+8+2,0,0,0);
    setContentsMargins(0,0,0,0);
    setLayout(mainLayout);
    setStyleSheet("height:29px;border:1px solid #eaeaea;border-radius:14px;");
}
void searchLine::setWordList(QStringList word_list)
{
	//构建模糊查询对象
	QCompleter *MyInfor = new QCompleter(word_list, this);
	MyInfor->setCaseSensitivity(Qt::CaseInsensitive);
	//设置Eidt的模糊查询对象
	this->setCompleter(MyInfor);
}
