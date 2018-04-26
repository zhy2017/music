#ifndef MIDDLEWIDGETS_H
#define MIDDLEWIDGETS_H

#include <QObject>
#include <QWidget>
#include "baseWidget.h"
#include "midleftwidget.h"
#include "midrightwidget.h"

class myPushButton;

class middleWidgets : public baseWidget
{
    Q_OBJECT
public:
    explicit middleWidgets(QWidget *parent = 0);
    void initLayout();

    midLeftWidget m_leftWid;
    midRightWidget m_rightWid;

protected:
    void mousePressEvent(QMouseEvent *){ setFocus(); }
    void mouseReleaseEvent(QMouseEvent *){}
    void mouseMoveEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);

};

#endif // MIDDLEWIDGETS_H
