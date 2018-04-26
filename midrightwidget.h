#ifndef MIDRIGHTWIDGET_H
#define MIDRIGHTWIDGET_H

#include <QObject>
#include <QWidget>
#include <QStackedWidget>
#include <QLineEdit>
#include <QLabel>

#include "baseWidget.h"
#include "myPushButton.h"

class midRightWidget : public baseWidget
{
    Q_OBJECT
public:
    explicit midRightWidget(QWidget*parent = 0);
    void init();
    void setDrawLine(bool draw = true){m_isdrawline = draw;}
    static QColor bgcolor;
     QStackedWidget m_stackWid;

public slots:
    void slot_btnClick();
    void slot_curStackChange();

protected:
   // void resizeEvent(QResizeEvent*);
    void paintEvent(QPaintEvent *);

private:
    bool m_isdrawline;
    myPushButton *m_btnArray[6];
    baseWidget m_wid;
};

#endif // MIDRIGHTWIDGET_H
