#include "mytablewidget.h"
#include<QDebug>
#include<QHeaderView>
#include<QScrollBar>
#include<qgridlayout.h>
#include<QMessageBox>
#include<QVBoxLayout>
#include <QApplication>


myTableWidget::myTableWidget(QWidget *parent):
    QTableWidget(parent)
    ,m_prebgItem(-1)
    ,m_loveNowRow(0)
    ,m_enter(false)
    ,m_isGiven(false)
    ,m_text("")
    ,m_playingWid(this)
    , m_addWid(this)
    ,m_Addtoplistmenu("添加到列表",&m_menu)
{
    init();
    initPlayingWidget();
    initMenu();
  //  connect(this,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(slot_doublick(int,int)));
  //  connect(this,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(slot_menuRequest(QPoint)));
  //  connect(this,SIGNAL(cellClicked(int,int)),this,SLOT(slot_cellClicked(int,int)));
  //  connect(this,SIGNAL(sig_RowCountChange()),this,SLOT(slot_rowCountChanged()));
}

void myTableWidget::initMenu()
{
    QAction*act_del = new QAction(QString("删除"), this);
    QAction*act_play = new QAction(QString("播放"), this);
    QAction*act_addsong = new QAction("添加歌曲", this);

    m_menu.addAction(act_play);
    m_menu.addAction(new QAction("稍后播", this));
    m_menu.addAction(new QAction("添加到播放列表          ", this));
    m_menu.addAction(new QAction("下载更多音质", this));
    m_menu.addSeparator();
    m_menu.addAction(act_addsong);
    m_menu.addAction(new QAction("排序", this));
    m_menu.addAction(new QAction("播放模式", this));
    m_menu.addAction(new QAction("匹配MV", this));
    m_menu.addSeparator();
    m_menu.addMenu(&m_Addtoplistmenu);
    m_menu.addAction(new QAction("移动到", this));
    m_menu.addAction(new QAction("相似歌曲", this));
    m_menu.addAction(new QAction("分享到", this));
    m_menu.addAction(new QAction("K歌", this));
    m_menu.addAction(new QAction("传歌到移动设备", this));
    m_menu.addAction(new QAction("传铃声到移动设备", this));
    m_menu.addAction(new QAction("工具", this));
    m_menu.addAction(new QAction("打开文件所在目录", this));
    m_menu.addAction(new QAction("歌曲信息", this));
    m_menu.addAction(new QAction("查看专辑", this));
    m_menu.addSeparator();
    m_menu.addAction(act_del);
    m_menu.addAction(new QAction("删除（包括文件）", this));
    m_menu.addAction(new QAction("重命名", this));
    m_menu.addSeparator();
    m_menu.addAction(new QAction("搜索~~", this));
    m_menu.addAction(new QAction("搜索~~", this));
    m_menu.setContentsMargins(4,10,3,10);
    m_Addtoplistmenu.setContentsMargins(4,10,3,10);

  //  connect(act_addsong,SIGNAL(triggered(bool)),this,SIGNAL(sig_addSong()));
 //   connect(act_del,SIGNAL(triggered(bool)),this,SLOT(slot_removeRow()));
  //  connect(act_play,SIGNAL(triggered(bool)),this,SLOT(slot_actplay()));
}
/*void myTableWidget::slot_menuRequest(QPoint)//请求菜单
{
    QVector<myTablePlayListFinal*> &plist=m_middleftStack0->myTablePlayListFinalVector();
    int index=0;
    foreach (myTablePlayListFinal*final, plist)
    {
        QAction* act=new QAction(final->ShowButtonName());
        act->setObjectName(QString::number(index));
        m_Addtoplistmenu.addAction(act);
        connect(act,SIGNAL(triggered(bool)),this,SLOT(slot_moveToPList()));
        index++;
        if(final==m_finalWidget)
        {
            act->setEnabled(false);
        }
    }
    if(rowCount()==0)
        return;
    int height2=QApplication::desktop()->height()-QCursor::pos().y();
    if(height2<m_menu.height())
    {
       m_menu.exec(QPoint(QCursor::pos().x(),height2));
    }
    else
    {
        m_menu.exec(QCursor::pos());
    }
    QList<QAction*> actlist=  m_Addtoplistmenu.actions();
    foreach (QAction* act, actlist)
    {
        act->deleteLater();
    }

}*/

void myTableWidget::init()
{

    setMouseTracking(true);
    setFrameShadow(QFrame::Plain);//设置平的样式
    setFrameShape(QFrame::NoFrame);//设置无边样式
    setFocusPolicy(Qt::NoFocus);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//水平scrollbar禁用
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::Expanding);
    setShowGrid(false);//隐藏线
    this->horizontalHeader()->setVisible(false);
    this->verticalHeader()->setVisible(false);
    setEditTriggers(QTableWidget::NoEditTriggers);//涓嶅彲缂栬緫
    setSelectionBehavior (QAbstractItemView::SelectRows); //璁剧疆閫夋嫨琛屼负锛屼互琛屼负鍗曚綅
    setSelectionMode (QAbstractItemView::ExtendedSelection);
    setContextMenuPolicy(Qt::CustomContextMenu);
    setAcceptDrops(true);

    insertColumn(0);
    insertColumn(1);
    insertColumn(2);
    horizontalHeader()->resizeSection(0,20);
    horizontalHeader()->resizeSection(1,170);
    horizontalHeader()->resizeSection(2,120);
    verticalHeader()->setDefaultSectionSize(32);//设置默认item高度的32

    setMinimumWidth(310);
    setMaximumWidth(380);
    setMinimumHeight(0);
    setStyleSheet("QTableWidget{color:rgb(48,48,48);}"
                  "QTableWidget::item:selected{background:rgb(180,180,180,100);}"
                  "QTableWidget::item{selection-color:rgb(38,38,38);}");
   // connect(this,SIGNAL(cellEntered(int,int)),this,SLOT(slot_cellEnter(int,int)));

  //  emit sig_RowCountChange();//发信号
}

void myTableWidget::initPlayingWidget()
{
    m_playingWid.raise();
    m_playingWid.hide();
    m_playingWid.installEventFilter(this);

    QHBoxLayout *hlyout = new QHBoxLayout;

    hlyout->addWidget(&m_addWid);
    hlyout->setContentsMargins(0, 0, 0, 0);
    setLayout(hlyout);

   // connect(&m_addWid.m_add,SIGNAL(clicked(bool)),this,SIGNAL(sig_addSong()));
   // connect(&m_addWid.m_addFolder,SIGNAL(clicked(bool)),this,SIGNAL(sig_addSongFolder()));
   // connect(&m_playingWid.m_btnDel,SIGNAL(clicked(bool)),this,SLOT(slot_playingWidgetDelBtnClicked()));
   // connect(&m_playingWid.m_btnLove,SIGNAL(clicked(bool)),this,SLOT(slot_playingWidgetLoveBtnClicked()));
}
