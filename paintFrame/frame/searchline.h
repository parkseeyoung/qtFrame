#ifndef SEARCHLINE_H
#define SEARCHLINE_H

#include <QLineEdit>
#include <QHBoxLayout>
#include <QPushButton>

class searchLine : public QLineEdit
{
    Q_OBJECT
public:
    searchLine(QWidget *parent = 0);
    QPushButton *searchBtn;
	void setWordList(QStringList word_list);
};

#endif // SEARCHLINE_H
