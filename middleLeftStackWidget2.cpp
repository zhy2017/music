#include "middleLeftStackWidget2.h"
#include "qlabel.h"
#include <QVBoxLayout>
middleLeftStackWidget2::middleLeftStackWidget2(QWidget*parent):baseWidget(parent)
{
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    init();
}
void middleLeftStackWidget2::init()
{
    QVBoxLayout *vLyout = new QVBoxLayout;
    m_wid=new buttonStackedWidget(this);
    m_wid->addPushButton("音乐电台");
    m_wid->addPushButton("MV电台");
    m_wid->showLayout();
    m_wid->m_stackwid->addWidget(new QWidget());
    m_wid->m_stackwid->addWidget(new QWidget());

    vLyout->addWidget(m_wid);
    vLyout->setContentsMargins(0, 0, 0,0 );
    setLayout(vLyout);

}
