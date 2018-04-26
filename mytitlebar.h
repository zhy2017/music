#ifndef MYTITLEBAR_H
#define MYTITLEBAR_H

#include <QWidget>

class QPoint;
enum CursorPos
{
    Default,
    Right,
    Left,
    Bottom,
    Top,
    TopRight,
    TopLeft,
    BottomRight,
    BottomLeft
};

class myTitleBar : public QWidget
{
    Q_OBJECT
public:
    explicit myTitleBar(QWidget *parent = 0);
    void mouseMoveRect(const QPoint &p);

private:
   // void paintEvent(QPaintEvent *event);
  //  void mouseDoubleClickEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    bool m_isPressed;
    QPoint m_startMovePos;
    CursorPos m_curPos;
    bool   IsPressBorder;
    QPoint  MousePos;
    QPoint  WindowPos;
    QSize PressedSize;
};

#endif // MYTITLEBAR_H
