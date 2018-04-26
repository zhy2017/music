#include "baseWidget.h"
#include <QStyleOption>
#include <QPainter>


baseWidget::baseWidget(QWidget *parent) : QWidget(parent)
{
    setStyleSheet("QWidget{background:transparent;}");
    setMouseTracking(true);
}
void baseWidget::paintEvent(QPaintEvent */*e*/)
{
    /* QWidget 的 paintEvent() 是空的，而样式表要通过 paint 被绘制到窗口中，
     * 我们需要重新写 paintEvent() 函数，才能够真正实现继承 */
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void baseWidget::mousePressEvent(QMouseEvent *e)
{
    QWidget::mousePressEvent(e);
}

void baseWidget::mouseMoveEvent(QMouseEvent *e)
{
    QWidget::mouseMoveEvent(e);
}

void baseWidget::mouseReleaseEvent(QMouseEvent *e)
{
    QWidget::mouseReleaseEvent(e);
}
