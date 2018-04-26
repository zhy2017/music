#include "midrightwidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPainter>
#include <QDebug>

QColor midRightWidget::bgcolor = QColor(230, 230, 230);//初始化

midRightWidget::midRightWidget(QWidget *parent) :
    baseWidget(parent),
    m_stackWid(this),
    m_wid(this)
{
    m_isdrawline = true;
    init();
    emit m_btnArray[0]->click();
}

void midRightWidget::init()
{
    setMinimumWidth(690);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QHBoxLayout *hlyout = new QHBoxLayout;
    QVBoxLayout *vlyout = new QVBoxLayout;

#if 0
    m_stackWid->addWidget(m_web0=new WebWidget(this));
    m_stackWid->addWidget(m_web1=new WebWidget(this));
    m_stackWid->addWidget(m_web2=new WebWidget(this));
    m_stackWid->addWidget(m_web3=new WebWidget(this));
    m_stackWid->addWidget(m_web4=new WebWidget(this));
    m_stackWid->addWidget(m_lrcwid=new LyricLabel(false,this));
    m_stackWid->addWidget(m_searchwid=new middleSearchWidget(this));

    m_web0->m_web->load(QUrl("http://www2.kugou.kugou.com/yueku/v9/html/home.html"));
    m_web0->m_web->settings()->setUserStyleSheetUrl(QUrl("qrc:/css/QWebViewStyle.css"));
    m_web0->m_web->show();

    m_web1->m_web->load(QUrl("http://www2.kugou.kugou.com/fm2/app/publicV2/html/recommend/index.html"));
    m_web1->m_web->settings()->setUserStyleSheetUrl(QUrl("qrc:/css/QWebViewStyle.css"));
    m_web1->m_web->show();

        m_web2->m_web->load(QUrl("http://www2.kugou.kugou.com/yueku/v9/html/default_special.html?ver=8071"));
        m_web2->m_web->settings()->setUserStyleSheetUrl(QUrl("qrc:/css/QWebViewStyle.css"));
        m_web2->m_web->show();

        m_web3->m_web->load(QUrl("http://www2.kugou.kugou.com/mv/v9/html/mvradio.html"));
        m_web3->m_web->settings()->setUserStyleSheetUrl(QUrl("qrc:/css/QWebViewStyle.css"));
        m_web3->m_web->show();

        m_web4->m_web->load(QUrl("http://fanxing.kugou.com/mini/index.html?ver=8071"));
        m_web4->m_web->settings()->setUserStyleSheetUrl(QUrl("qrc:/css/QWebViewStyle.css"));
        m_web4->m_web->show();

 #else
        m_stackWid.addWidget(new baseWidget(this));
        m_stackWid.addWidget(new baseWidget(this));
        m_stackWid.addWidget(new baseWidget(this));
        m_stackWid.addWidget(new baseWidget(this));
        m_stackWid.addWidget(new baseWidget(this));
        m_stackWid.addWidget(new baseWidget(this));
        m_stackWid.addWidget(new baseWidget(this));
#endif
    m_btnArray[0] = new myPushButton(this);
    m_btnArray[1] = new myPushButton(this);
    m_btnArray[2] = new myPushButton(this);
    m_btnArray[3] = new myPushButton(this);
    m_btnArray[4] = new myPushButton(this);
    m_btnArray[5] = new myPushButton(this);

    m_btnArray[0]->setText("乐库");
    m_btnArray[1]->setText("电台");
    m_btnArray[2]->setText("歌单");
    m_btnArray[3]->setText("直播");
    m_btnArray[4]->setText("MV");
    m_btnArray[5]->setText("歌词");


    m_btnArray[0]->setFixedSize(54, 40);
    m_btnArray[1]->setFixedSize(54, 40);
    m_btnArray[2]->setFixedSize(54, 40);
    m_btnArray[3]->setFixedSize(54, 40);
    m_btnArray[4]->setFixedSize(54, 40);
    m_btnArray[5]->setFixedSize(54, 40);

    m_btnArray[0]->setStyleSheet("QPushButton{color:rgb(68,68,68);font-size:17px;font-family:黑体;}"
                         "QPushButton:hover{color:rgb(40,143,231);}");
    m_btnArray[1]->setStyleSheet("QPushButton{color:rgb(68,68,68);font-size:17px;font-family:黑体;}"
                          "QPushButton:hover{color:rgb(40,143,231);}");
    m_btnArray[2]->setStyleSheet("QPushButton{color:rgb(68,68,68);font-size:17px;font-family:黑体;}"
                          "QPushButton:hover{color:rgb(40,143,231);}");
    m_btnArray[3]->setStyleSheet("QPushButton{color:rgb(68,68,68);font-size:17px;font-family:黑体;}"
                          "QPushButton:hover{color:rgb(40,143,231);}");
    m_btnArray[4]->setStyleSheet("QPushButton{color:rgb(68,68,68);font-size:17px;font-family:黑体;}"
                          "QPushButton:hover{color:rgb(40,143,231);}");
    m_btnArray[5]->setStyleSheet("QPushButton{color:rgb(68,68,68);font-size:17px;font-family:黑体;}"
                          "QPushButton:hover{color:rgb(40,143,231);}");

    hlyout->addStretch(60);
    hlyout->addWidget(m_btnArray[0], 0, Qt::AlignHCenter);
    hlyout->addWidget(m_btnArray[1], 0, Qt::AlignHCenter);
    hlyout->addWidget(m_btnArray[2], 0, Qt::AlignHCenter);
    hlyout->addWidget(m_btnArray[3], 0, Qt::AlignHCenter);
    hlyout->addWidget(m_btnArray[4], 0, Qt::AlignHCenter);
    hlyout->addWidget(m_btnArray[5], 0, Qt::AlignHCenter);

    hlyout->addStretch(60);
    hlyout->setSpacing(25);
    hlyout->setContentsMargins(0, 0, 0, 0);
    for(int i = 0; i < 6; i++)
    {
       m_btnArray[i]->setObjectName(QString::number(i));
       connect(m_btnArray[i], SIGNAL(clicked()), this, SLOT(slot_curStackChange()));
    }

    m_wid.setLayout(hlyout);
    vlyout->addWidget(&m_wid);
    vlyout->addWidget(&m_stackWid);
    vlyout->setSpacing(0);
    vlyout->setContentsMargins(0, 0, 0, 0);
    setLayout(vlyout);
  //  m_stackWid.setCurrentIndex(1);
   // connect(&m_stackWid, SIGNAL(currentChanged(int)), this, SLOT(slot_curStackChange(int)));
}

void midRightWidget::slot_btnClick()
{
   // qDebug() << 1;
    int index = sender()->objectName().toInt();
  //  qDebug() << index;
    m_stackWid.setCurrentIndex(index);
}

void midRightWidget::slot_curStackChange()
{
  //  qDebug() << 2;
    int index = sender()->objectName().toInt();
  //  qDebug() << index;
    m_stackWid.setCurrentIndex(index);
    for(int i = 0; i < 6; i++)
    {
        if(i == index)
            m_btnArray[i]->setStyleSheet("QPushButton{border-image: url(:/image/middlewidget/btn_mask.png); color:rgb(40,143,231);font-size:17px;font-family:黑体;}");
        else
            m_btnArray[i]->setStyleSheet("QPushButton{color:rgb(68,68,68);font-size:17px;font-family:黑体;}"
                                           "QPushButton:hover{color:rgb(40,143,231);}");
    }
}

void midRightWidget::paintEvent(QPaintEvent *e)
{
    baseWidget::paintEvent(e);
    if(m_isdrawline)
    {
        QPainter p(this);
        p.setPen(bgcolor);
        p.drawLine(0, 39, width(), 39);
    }
}
