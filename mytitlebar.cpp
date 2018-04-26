#include "mytitlebar.h"
#include <QPoint>
#include <QMouseEvent>
#include <QDebug>

#define border 4

myTitleBar::myTitleBar(QWidget *parent) : QWidget(parent)
{
    setMouseTracking(true);
    m_isPressed = false;
    IsPressBorder = false;
}

void myTitleBar::mouseMoveRect(const QPoint &p)
{
    if(!IsPressBorder)
    {
        if(p.x() < this->parentWidget()->x() + border && p.y() > this->parentWidget()->y() && p.y() < this->parentWidget()->y() + border)
        {
            m_curPos = TopLeft;
            setCursor(Qt::SizeFDiagCursor);
        }
        else if(p.x() > this->parentWidget()->x() + this->parentWidget()->width() - border && p.y() > this->parentWidget()->y() && p.y() < this->parentWidget()->y() + border)
        {
            m_curPos = TopRight;
            setCursor(Qt::SizeBDiagCursor);
        }
        else if(p.x() > this->parentWidget()->x() + this->parentWidget()->width() - border)//right side
        {
            m_curPos = Right;
            setCursor(Qt::SizeHorCursor);
        }
        else if(p.x() < this->parentWidget()->x() + border)//left side;
        {
            m_curPos = Left;
            setCursor(Qt::SizeHorCursor);
        }
        else if(p.y() > this->parentWidget()->y() && p.y() < this->parentWidget()->y() + border)
        {
            m_curPos = Top;
            setCursor(Qt::SizeVerCursor);
        }
        else
        {
            m_curPos = Default;
            setCursor(Qt::ArrowCursor);
        }
    }
}

void myTitleBar::mousePressEvent(QMouseEvent *event)
{
    PressedSize = this->parentWidget()->size();
    IsPressBorder = false;
    setFocus();
    if(event->button() == Qt::LeftButton)
    {
        WindowPos = this->pos();
        if(QRect(x() + border, y() + border, width() - 2 * border, height() - border).contains(event->pos()))
        {
            m_isPressed = true;
            m_startMovePos = event->globalPos();
        }
        else
        {
            IsPressBorder = true;
        }
    }
    return QWidget::mousePressEvent(event);
}

void myTitleBar::mouseMoveEvent(QMouseEvent *event)
{
    mouseMoveRect((event->globalPos()));
    if (m_isPressed)
    {
        QPoint movePoint = event->globalPos() - m_startMovePos;
        QPoint widgetPos = this->parentWidget()->pos();
        m_startMovePos = event->globalPos();
        this->parentWidget()->move(widgetPos.x() + movePoint.x(), widgetPos.y() + movePoint.y());
    }
    if(IsPressBorder)
    {
        switch(m_curPos)
        {

        case CursorPos::Right:
        {
            int moveWidth = event->globalX() - this->parentWidget()->x();
            if(moveWidth > this->parentWidget()->minimumWidth())
            {
                this->parentWidget()->setGeometry(this->parentWidget()->x(), this->parentWidget()->y(), moveWidth, this->parentWidget()->height());
            }
            break;
        }

        case CursorPos::Left:
        {
            int moveWidth = this->parentWidget()->x() + this->parentWidget()->width() - event->globalX();
            if(moveWidth > this->parentWidget()->minimumWidth())
            {
                this->parentWidget()->setGeometry(event->globalX(), this->parentWidget()->y(), moveWidth, this->parentWidget()->height());
            }
            break;
        }

        default:
            break;
        }
    }
    return QWidget::mouseMoveEvent(event);
}

void myTitleBar::mouseReleaseEvent(QMouseEvent *event)
{
    m_isPressed = false;
    IsPressBorder = false;
    return QWidget::mouseReleaseEvent(event);
}
