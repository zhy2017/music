#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "TextMovingWidget.h"
#include "mySlider.h"
#include "mypushbutton.h"
#include "middleWidgets.h"

namespace Ui {
class Widget;
}

class QPixmap;

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    void init();
    void bottomWidgetInit();
    void topWidgetInit();

public slots:
   void setSkin(const QString &str);

protected:
   virtual void paintEvent(QPaintEvent *e);

private slots:
   void on_miniBtn_clicked();

   void on_closeBtn_clicked();

private:
    Ui::Widget *ui;
    QPixmap m_curPix;
    QString m_curPixPath;
    TextMovingWidget *m_labnowPlayname;
    mySlider *m_mainslider;
    volButton *m_volButton;
    mySlider *m_volslider;
    middleWidgets *m_midWidget;
};

#endif // WIDGET_H
