#include "middleLeftStackWidget0.h"
#include <QLabel>
#include <QScrollBar>
#include <QVBoxLayout>
#include <QDebug>
#include <QDrag>
#include <QDropEvent>
#include <QMimeData>

#include"tablewidgetplaylist/myTablePlayListFinal.h"
#include"tablewidgetplaylist/mytablewidget.h"
#include"tablewidgetplaylist/playingWidget.h"
#include"middleWidgets.h"

middleLeftStackWidget0::middleLeftStackWidget0(QWidget*parent)
    :myScrollArea(parent)
    ,m_wid(this)
    ,m_defaultList(this)
    ,m_lovedList(this)
{
    setMinimumWidth(310);
    setMaximumWidth(380);
    init();
}

void middleLeftStackWidget0::init()
{
    setMouseTracking(true);
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    setWidget(&m_wid);
    QGridLayout *glyout = new QGridLayout;
    glyout->addWidget(&m_wid);
    glyout->setContentsMargins(0, 0, 0, 0);
    setLayout(glyout);

    //m_defaultList.setMiddleStackWidget0(this);
    m_defaultList.setShowButtonName(QString("默认列表"));
   // m_defaultList.getlistfromDateBase();//添加歌曲
    //m_defaultList.m_table.show();
  //  m_defaultList.m_Btntable.setEnabledMenuItem();

   // m_lovedList.setMiddleStackWidget0(this);
    m_lovedList.setShowButtonName(QString("我的最爱"));
  //  m_lovedList.getlistfromDateBase();
  //  m_lovedList.m_table.hide();
  //  m_lovedList.m_Btntable.setEnabledMenuItem();

    m_Vector << &m_defaultList << &m_lovedList;
    m_vlyout.addWidget(&m_defaultList);
    m_vlyout.addWidget(&m_lovedList);


    m_vlyout.addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding));
    m_vlyout.setContentsMargins(0, 0, 0, 0);
    m_vlyout.setSpacing(0);
    m_wid.setLayout(&m_vlyout);

   setAutoLayout();
  // setMouseTracking(true);
   // setOriginalStatus();
}

void middleLeftStackWidget0::setAutoLayout()
{
  int height = 0;
  foreach(myTablePlayListFinal* p, m_Vector)
  {
      height += p->height();
  }
  m_wid.setMinimumHeight(height);
}

myScrollArea::myScrollArea(QWidget *parent):QScrollArea(parent)
{

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setFrameShadow(QFrame::Plain);//设置平的样式
    setFrameShape(QFrame::NoFrame);//设置无边样式

    verticalScrollBar()->setStyleSheet("QScrollBar{background:transparent; width:10px; padding-right: 2px;}"
                                      "QScrollBar::handle{background:rgb(180,180,180,150);border-radius:4px;}"
                                      "QScrollBar::handle:hover{background: rgb(150,150,150,150);}"
                                      "QScrollBar::add-line:vertical{border:1px rgb(230,230,230,150);height: 1px;}"
                                      "QScrollBar::sub-line:vertical{border:1px rgb(230,230,230,150);height: 1px;}"
                                      "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {background:transparent;}");


//////////////////////////////////////////////用于最外边


}

