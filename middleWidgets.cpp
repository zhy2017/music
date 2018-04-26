#include "middleWidgets.h"

#include "myPushButton.h"
#include "QHBoxLayout"
#include <QPainter>

middleWidgets::middleWidgets(QWidget *parent)
    : baseWidget(parent),
      m_leftWid(this),
      m_rightWid(this)
{
    setStyleSheet("baseWidget{background:white;}");
    initLayout();
}

void middleWidgets::initLayout()
{
    QHBoxLayout *hyout = new QHBoxLayout;

    hyout->addWidget(&m_leftWid);
    hyout->addWidget(&m_rightWid);
    hyout->setSpacing(0);
    hyout->setContentsMargins(0, 0, 0, 0);
    setLayout(hyout);
}

void middleWidgets::mouseMoveEvent(QMouseEvent *e)
{
    baseWidget::mouseMoveEvent(e);
}

void middleWidgets::paintEvent(QPaintEvent *e)
{
    baseWidget::paintEvent(e);
  /*  QPainter p(this);
    p.setPen(QColor(230,230,230));
    p.drawLine(QPoint(0,0),QPoint(width(),0));
    p.drawLine(QPoint(0,height()-1),QPoint(width(),height()-1));*/
}
