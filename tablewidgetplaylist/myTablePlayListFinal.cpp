#include "myTablePlayListFinal.h"
#include <QVBoxLayout>
#include <QScrollBar>
#include <QFileDialog>
#include <iterator>
#include <QToolTip>
#include <QMessageBox>
#include <QEventLoop>
#include <QTime>
#include <qthread.h>
#include <QPainter>
#include <QMimeData>

#include"mytablewidget.h"

static QColor BGcolor = QColor(230,230,230);

myTablePlayListFinal::myTablePlayListFinal(QWidget*parent):
    baseWidget(parent)
{
   // m_table.setTableFinal(this);
   // m_Btntable.setTableFinal(this);
 //   m_playList.setTableFinal(this);

    setMouseTracking(true);
 //   setAcceptDrops(true);

 //   connect(&m_Btntable,SIGNAL(sig_emptyList()),this,SLOT(slot_emptyList()));//清空列表
 //   connect(&m_Btntable,SIGNAL(sig_addSong()),this,SLOT(slot_addSong()));//添加歌曲
 //   connect(&m_table,SIGNAL(sig_RowCountChange()),&m_Btntable,SLOT(slot_updateSongCount()));//歌曲列表改变信息
 //   connect(&m_table,SIGNAL(sig_RowCountChange()),&m_Btntable,SLOT(slot_updateSongCount()));//歌曲列表改变信息
 //   connect(&m_Btntable,SIGNAL(clicked(bool)),this,SLOT(slot_showHideTable()));
 //   connect(&m_table,SIGNAL(sig_delIndex(int)),&m_playList,SLOT(slot_removeSong(int)));//从列表中删除
 //   connect(&m_table,SIGNAL(sig_addSong()),this,SLOT(slot_addSong()));//添加歌曲
 //   connect(&m_table,SIGNAL(sig_addSongFolder()),this,SLOT(slot_addSongFolder()));

    QVBoxLayout *vlyout1 = new QVBoxLayout;
    setMinimumSize(310, 40);
    setMaximumWidth(380);

    vlyout1->addWidget(&m_Btntable);
  //  vlyout1->addWidget(&m_table);
    vlyout1->setContentsMargins(0, 0, 0, 0);
    vlyout1->setSpacing(0);
    setLayout(vlyout1);
}
