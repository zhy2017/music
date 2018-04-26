#include "myshowtablebutton.h"
#include <QHBoxLayout>
#include "midleftwidget.h"
#include <QPainter>

myShowTableButton::myShowTableButton(QWidget*parent)
    :QPushButton(parent)
    ,m_indicator(this)
    ,m_btnmenu(this)
    ,m_lineEdit(this)
    ,m_playlistName("",this)
{
    m_isdrawMove = false;
    setAcceptDrops(true);
   // setMouseTracking(true);
    init();
    initMenu();
    setFixedHeight(40);
}

void myShowTableButton::init()
{
    m_isTipsStyle = false;
    setCursor(Qt::PointingHandCursor);
   // setAcceptDrops(true);

    m_lineEdit.setGeometry(16, 5, 250, 30);
    m_lineEdit.setContextMenuPolicy(Qt::NoContextMenu);
    m_lineEdit.setStyleSheet("QLineEdit{border:4px solid rgb(40,80,150);}");
    m_lineEdit.installEventFilter(this);
    m_lineEdit.raise();
    m_lineEdit.hide();

    QHBoxLayout *lyout = new QHBoxLayout(this);

    m_playlistName.setStyleSheet("color:rgb(38,38,38);font: 15px 黑体;");

    m_indicator.setFixedSize(16, 16);
    m_btnmenu.setFixedSize(16, 16);

    m_indicator.setStyleSheet("QLabel{border-image:url(:/image/middlewidget/indicator_top (1).png);}"
                               "QLabel:hover{border-image:url(:/image/middlewidget/indicator_top (2).png);}"
                               "QLabel:pressed{border-image:url(:/image/middlewidget/indicator_top (1).png);}");

    m_btnmenu.setStyleSheet("QPushButton{border-image:url(:/image/middlewidget/indicator_menu (1).png);}"
                             "QPushButton:hover{border-image:url(:/image/middlewidget/indicator_menu (2).png);}"
                             "QPushButton:pressed{border-image:url(:/image/middlewidget/indicator_menu (3).png);}");


    lyout->addWidget(&m_indicator, 0, Qt::AlignVCenter);
    lyout->addWidget(&m_playlistName, 0, Qt::AlignVCenter);

    lyout->addSpacerItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Fixed));
    lyout->addWidget(&m_btnmenu, 0, Qt::AlignVCenter);
    lyout->addSpacing(14);
    lyout->setContentsMargins(0, 0, 0, 0);
    lyout->setSpacing(2);
    setLayout(lyout);

    connect(&m_lineEdit, SIGNAL(returnPressed()), this,SLOT(setFocus()));
    connect(&m_btnmenu, SIGNAL(clicked(bool)), this, SLOT(slot_menuRequest()));
}

 void myShowTableButton::initMenu()
 {
     QAction *act_addplaylist = new QAction(("新建列表"), NULL);
     QAction *act_addsong = new QAction(("添加歌曲"), NULL);
     QAction *act_delplayList = new QAction(("删除列表"), NULL);
     QAction *act_reName = new QAction(("重命名"), NULL);
     QAction* act_emptyList = new QAction(("清空列表"), NULL);

     m_menu.addAction(act_addplaylist);
     m_menu.addSeparator();
     m_menu.addAction(act_addsong);
     m_menu.addAction(new QAction(tr("稍后播"), NULL));
     m_menu.addAction(new QAction(tr("添加到播放列表"), NULL));
     m_menu.addAction(new QAction(tr("全部发送到移动设备"), NULL));
     m_menu.addAction(new QAction(tr("下载本列表全部歌曲"), NULL));
     m_menu.addAction(new QAction(tr("排序"), NULL));
     m_menu.addAction(new QAction(tr("匹配MV"), NULL));
     m_menu.addAction(new QAction(tr("收藏整个列表"), NULL));
     m_menu.addSeparator();
     m_menu.addAction(act_emptyList);
     m_menu.addAction(act_delplayList);
     m_menu.addAction(act_reName);
     m_menu.setContentsMargins(4, 10, 3, 10);
     m_menu.actionGeometry(act_reName);//一定不能删除 setEnabledMenuItem要工作必须要它 可能是一个bug// must to call this function if not the setEnabledMenuItem function cant work correctly;

     m_menu.setStyleSheet("QMenu{background-color: white;border: 1px solid rgb(214,214,214);border-radius:10px;}"
                    "QMenu::item{height: 28px;padding: 0px 20px 0px 40px;font-size : 12px;color: rgb(102, 102, 102);font-family: 微软雅黑;}"
                    "QMenu::item:focus{padding: -1;}"
                    "QMenu::item:!enabled{color:gray;}"
                    "QMenu::item:selected{color: white;background-color: rgb(22, 154, 243);}"
                    "QMenu::icon{position: absolute;left: 12px;}"
                    "QMenu::separator{height:1px;background: rgb(209,209,209);margin:4px 0px 4px 0px;}");
     //connect(act_emptyList,SIGNAL(triggered(bool)),this,SIGNAL(sig_emptyList()));
    // connect(act_reName,SIGNAL(triggered(bool)),this,SLOT(slot_ReName()));
    // connect(act_delplayList,SIGNAL(triggered(bool)),this,SIGNAL(sig_delPlayList()));
  //   connect(act_addplaylist,SIGNAL(triggered(bool)),this,SIGNAL(sig_addPlayList()));
  //   connect(act_addsong,SIGNAL(triggered(bool)),this,SIGNAL(sig_addSong()));
   //  connect(this,SIGNAL(sig_reName(QString)),this,SLOT(slot_reNameDB(QString)));
 }

 void myShowTableButton::setTableShowIndicator(bool bShow)
{
     if(bShow)
     {
         m_indicator.setStyleSheet("QLabel{border-image:url(:/image/middlewidget/indicator_down (1).png);}"
                                    "QLabel:hover{border-image:url(:/image/middlewidget/indicator_down (2).png);}"
                                    "QLabel:pressed{border-image:url(:/image/middlewidget/indicator_down (1).png);}");
     }
     else
     {
         m_indicator.setStyleSheet("QLabel{border-image:url(:/image/middlewidget/indicator_top (1).png);}"
                                    "QLabel:hover{border-image:url(:/image/middlewidget/indicator_top (2).png);}"
                                    "QLabel:pressed{border-image:url(:/image/middlewidget/indicator_top (1).png);}");
     }

}

 void myShowTableButton::setEnabledMenuItem(bool isSetting)
{
    m_menu.actionAt(QPoint(5, 309))->setEnabled(isSetting);//del
    m_menu.actionAt(QPoint(5, 337))->setEnabled(isSetting);//rename
}

 void myShowTableButton::setTipsStyle(bool isset)
 {
     m_isTipsStyle = isset;
     setTableShowIndicator();
     update();
 }


 void myShowTableButton::dragLeaveEvent(QDragLeaveEvent *)
 {
     m_isdrawMove=false;
     m_isdrawTop=false;
     update();
 }

 void myShowTableButton::mousePressEvent(QMouseEvent *e)
 {
     if(e->button()==Qt::LeftButton)
     {
         QPushButton::mousePressEvent(e);
     }
     m_presspos=e->pos();
 }

 void myShowTableButton::dragMoveEvent(QDragMoveEvent *e)
 {
    /*if(e->mimeData()->hasFormat(mimeType()) && mainWindow::GetInstance()->middleStack0()->isEnableMoveList(m_finalWid))
    {
        m_isdrawMove=true;
        if(e->pos().y()<height()/2)
        {
            m_isdrawTop=true;
            update();
        }
        else
        {
            m_isdrawTop=false;
            update();
        }
    }*/
 }

 void myShowTableButton::dragEnterEvent(QDragEnterEvent *event)
 {
   /*  if(event->mimeData()->hasFormat(mimeType()))
     {
         event->setDropAction(Qt::MoveAction);
         event->accept();
     }
     else
         event->ignore();*/
 }

 void myShowTableButton::dropEvent(QDropEvent *e)
 {
   /*   m_isdrawMove=false;
      update();
      middleLeftStackWidget0*pMidStack0=mainWindow::GetInstance()->middleStack0();
     if(e->mimeData()->hasFormat(mimeType())&&pMidStack0->isEnableMoveList(m_finalWid))
     {
        QByteArray byt= e->mimeData()->data(mimeType());
        int index= byt.toInt();
        if(m_isdrawTop)
        {
             int targetIndex= pMidStack0->myTablePlayListFinalVector().indexOf(m_finalWid);
             pMidStack0->setListTakeAndInsert(pMidStack0->myTablePlayListFinalVector().value(index),pMidStack0->myTablePlayListFinalVector().value(targetIndex-1));
        }
        else
        {
            pMidStack0->setListTakeAndInsert(pMidStack0->myTablePlayListFinalVector().value(index),m_finalWid);
        }
     }*/
 }

 void myShowTableButton::mouseMoveEvent(QMouseEvent *e)
 {
     /*QRect re(m_presspos.x() - 2, m_presspos.y() - 2, m_presspos.x() + 2, m_presspos.y() + 2);
     if(!re.contains(e->pos())&&mainWindow::GetInstance()->middleStack0()->isEnableMoveList(m_finalWid))
     {
         int index= mainWindow::GetInstance()->middleStack0()->myTablePlayListFinalVector().indexOf(m_finalWid);
     //! [15]
         QMimeData *mimeData=new QMimeData; //自动释放
         mimeData->setData(mimeType(), QString::number(index).toUtf8());
         mimeData->setText(m_finalWid->ShowButtonName());

         QDrag *drag = new QDrag(this); //自动释放
         drag->setMimeData(mimeData);

         QPixmap pixmap =this->grab(rect());
         drag->setHotSpot(QPoint(0,height()/2));
         drag->setPixmap(pixmap);
     //! [17]
         drag->exec(Qt::MoveAction);
         if(drag)
             drag->deleteLater();
         if(mimeData)
             mimeData->deleteLater();
     }*/
 }


 bool myShowTableButton::eventFilter(QObject *o, QEvent *e)
 {
     if(o == &m_lineEdit)
     {
         if(e->type()==QEvent::FocusOut)//
         {
             //slot_returnPressed();
         }
     }
     return QObject::eventFilter(o,e);
 }

 void myShowTableButton::paintEvent(QPaintEvent *)
 {
     if(m_isTipsStyle)
     {
         QPainter painter(this);
         QLinearGradient gradient;
         gradient.setStart(0, 37);
         gradient.setFinalStop(0, height());
         gradient.setColorAt(0.1, QColor(150,150,150,150));
         gradient.setColorAt(0.9, QColor(180,180,180,50));

         painter.setPen(Qt::transparent);
         painter.setBrush(gradient);
         painter.drawRect(0, 37, width(), height());

       /*  if(mainWindow::GetInstance())
         {
             if(mainWindow::GetInstance()->m_mainwid->CurrentIndex()==5)
                 painter.drawPixmap(0,0,width(),height()-3
                             ,mainWindow::GetInstance()->m_mainwid->getRectPix(QRect(0,90,width(),height()-3)));
             else
             {
                 painter.setBrush(Qt::white);
                 painter.drawRect(-1,0,width(),height()-3);
             }
         }*/
         painter.setBrush(midLeftWidget::bgcolor);
         painter.drawRect(-1, 0, width(), height() - 3);
     }

     if(m_isdrawMove)
     {
         QPainter p(this);
         if(m_isdrawTop)
         {
             p.drawLine(0, 0, width(), 0);
         }
         else
         {
             p.drawLine(0, height() - 1, width(), height() - 1);
         }
     }
 }

 void myShowTableButton::mouseReleaseEvent(QMouseEvent*e)
 {
     if(e->button() == Qt::RightButton)
     {
          m_menu.exec(QCursor::pos());
     }
     QPushButton::mouseReleaseEvent(e);
 }
