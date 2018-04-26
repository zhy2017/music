#ifndef MIDDLELEFTSTACKWIDGET2_H
#define MIDDLELEFTSTACKWIDGET2_H

#include <QObject>
#include <QWidget>
#include"baseWidget.h"
#include"buttonstackedwidget.h"
class middleLeftStackWidget2:public baseWidget
{
    Q_OBJECT
public:
   explicit middleLeftStackWidget2(QWidget *parent);
    buttonStackedWidget *m_wid;
    void init();
};

#endif // MIDDLELEFTSTACKWIDGET4_H
