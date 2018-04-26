#include "widget.h"
#include "ui_widget.h"
#include <QPixmap>
#include <QPainter>
#include <QtMath>
#include <QDebug>
#include "mypushbutton.h"
#include <QHBoxLayout>
#include <QVBoxLayout>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    init();
    bottomWidgetInit();
    topWidgetInit();

    m_midWidget = new middleWidgets(this);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(ui->topWidget);
    mainLayout->addWidget(m_midWidget);
   // mainLayout->addWidget(ui->midWidget);
    mainLayout->addWidget(ui->bottomWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    setLayout(mainLayout);
}

Widget::~Widget()
{
   // qDebug() << "close1";
    delete ui;
  //  qDebug() << "close2";
    delete m_midWidget;
}

void Widget::init()
{
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);
    setAttribute(Qt::WA_TranslucentBackground);

    setSkin(":/skin/1.png");
    this->move(200, 40);
}

void Widget::bottomWidgetInit()
{
    ui->nextBtn->setStyleSheet("QPushButton{border-image:url(:/image/bottomwidget/btn_next (1).png);}"
                             "QPushButton::hover{border-image:url(:/image/bottomwidget/btn_next (2).png);}"
                             "QPushButton::pressed{border-image:url(:/image/bottomwidget/btn_next (3).png);}");
    ui->previousBtn->setStyleSheet("QPushButton{border-image:url(:/image/bottomwidget/btn_previous (1).png);}"
                                 "QPushButton::hover{border-image:url(:/image/bottomwidget/btn_previous (2).png);}"
                                 "QPushButton::pressed{border-image:url(:/image/bottomwidget/btn_previous (3).png);}");
    ui->playBtn->setStyleSheet("QPushButton{border-image:url(:/image/bottomwidget/btn_play (1).png);}"
                             "QPushButton::hover{border-image:url(:/image/bottomwidget/btn_play (2).png);}"
                               "QPushButton::pressed{border-image:url(:/image/bottomwidget/btn_play (3).png);}");
    QHBoxLayout *layout1 = new QHBoxLayout();
    layout1->addWidget(ui->previousBtn);
    layout1->addWidget(ui->playBtn);
    layout1->addWidget(ui->nextBtn);
    layout1->setSpacing(15);

    m_mainslider = new mySlider(Qt::Horizontal, ui->bottomWidget);
    m_mainslider->installEventFilter(this);
    m_mainslider->setRange(0, 1000);
    m_mainslider->setMinimumSize(300, 12);
    m_mainslider->setMaximumHeight(12);
    m_mainslider->setStyleSheet("QSlider::groove:horizontal{border-radius:2px;height:3px;}"
                               "QSlider::sub-page:horizontal{background:rgb(255, 255, 160);}"
                               "QSlider::add-page:horizontal{background:rgb(200,200,209);}"
                               "QSlider::handle:horizontal{background:rgb(255, 255, 160);width:8px;border-radius:4px;margin:-3px 0px -3px 0px;}");

    QFont font;
    font.setFamily("微软雅黑");
    font.setPixelSize(14);
    font.setBold(true);

    m_labnowPlayname = new TextMovingWidget("蘑菇音乐", ui->bottomWidget);

    QHBoxLayout *layout2_1 = new QHBoxLayout();

    m_labnowPlayname->setMinimumWidth(200);
    m_labnowPlayname->setFixedHeight(30);
    m_labnowPlayname->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    m_labnowPlayname->setFont(font);

    font.setPixelSize(12);
    font.setBold(false);

    ui->positionLab->setAlignment(Qt::AlignRight | Qt::AlignBottom);
    ui->positionLab->setFont(font);

    QPalette palette;
    palette.setColor(QPalette::WindowText, Qt::white);
    ui->positionLab->setPalette(palette);


    layout2_1->addWidget(m_labnowPlayname);
    layout2_1->addWidget(ui->positionLab);
    layout2_1->setSpacing(0);
    layout2_1->setContentsMargins(0, 0, 0, 0);

    QVBoxLayout *vlayout = new QVBoxLayout();
    vlayout->addLayout(layout2_1);
    vlayout->addWidget(m_mainslider);
    vlayout->setSpacing(0);
    vlayout->setContentsMargins(0, 0, 0, 10);

   // m_volButton = new volButton(":/image/bottomwidget/btn_vol (1).png", ":/image/bottomwidget/btn_vol (2).png", ":/image/bottomwidget/btn_vol (3).png", ui->bottomWidget);

    ui->volBtn->setStyleSheet("QPushButton{border-image:url(:/image/bottomwidget/vol1.png);}"
                              "QPushButton::hover{border-image:url(:/image/bottomwidget/vol2.png);}"
                              "QPushButton::pressed{border-image:url(:/image/bottomwidget/vol1.png);}");
    ui->favoriteBtn->setStyleSheet("QPushButton{border-image:url(:/image/bottomwidget/btn_favorite_no (1).png);}"
                                   "QPushButton::hover{border-image:url(:/image/bottomwidget/btn_favorite_no (2).png);}"
                                   "QPushButton::pressed{border-image:url(:/image/bottomwidget/btn_favorite_no (3).png);}");
    ui->downloadBtn->setStyleSheet("QPushButton{border-image:url(:/image/bottomwidget/down1.png);}"
                                   "QPushButton::hover{border-image:url(:/image/bottomwidget/down2.png);}"
                                   "QPushButton::pressed{border-image:url(:/image/bottomwidget/down1.png);}");
    ui->moreBtn->setStyleSheet("QPushButton{border-image:url(:/image/bottomwidget/btn_more (1).png);}"
                               "QPushButton::hover{border-image:url(:/image/bottomwidget/btn_more (2).png);}"
                               "QPushButton::pressed{border-image:url(:/image/bottomwidget/btn_more (3).png);}");
    ui->playmoreBtn->setStyleSheet("QPushButton{border-image:url(:/image/bottomwidget/btn_listrandom (1).png);}"
                                   "QPushButton::hover{border-image:url(:/image/bottomwidget/btn_listrandom (2).png);}");
    ui->equalizerBtn->setStyleSheet("QPushButton{border:NULL;background-image:url(:/image/bottomwidget/btn_equalizer (1).png);}"
                                    "QPushButton::hover{background-image:url(:/image/bottomwidget/btn_equalizer (2).png);}"
                                    "QPushButton::pressed{background-image:url(:/image/bottomwidget/btn_equalizer (3).png);}");
    ui->lrcBtn->setStyleSheet("QPushButton{border-image:url(:/image/bottomwidget/btn_lrc (1).png);}"
                              "QPushButton::hover{border-image:url(:/image/bottomwidget/btn_lrc (2).png);}"
                              "QPushButton::pressed{border-image:url(:/image/bottomwidget/btn_lrc (3).png);}");
    ui->playlistBtn->setStyleSheet("QPushButton{border-image:url(:/image/bottomwidget/btn_miniplaylist (1).png) 0 44 0 0;}"
                                   "QPushButton::hover{border-image:url(:/image/bottomwidget/btn_miniplaylist (2).png) 0 44 0 0;}"
                                   "QPushButton::pressed{border-image:url(:/image/bottomwidget/btn_miniplaylist (3).png) 0 44 0 0;}");

    m_volslider = new mySlider(Qt::Horizontal, ui->bottomWidget);
    m_volslider->installEventFilter(this);
    m_volslider->setRange(0, 100);
    m_volslider->setFixedSize(80, 12);
    m_volslider->setStyleSheet("QSlider::groove:horizontal{border-radius:2px;height:3px;}"
                               "QSlider::sub-page:horizontal{background:rgb(255, 255, 160);}"
                              "QSlider::add-page:horizontal{background:rgb(200,200,209);}"
                               "QSlider::handle:horizontal{background:rgb(255, 255, 160);width:8px;border-radius:4px;margin:-3px 0px -3px 0px;}");
    QHBoxLayout *layout3 = new QHBoxLayout();
    layout3->addWidget(ui->volBtn);
    layout3->addWidget(m_volslider);
    layout3->setSpacing(5);
    layout3->setContentsMargins(0, 0, 0, 0);


    QHBoxLayout *layout2 = new QHBoxLayout();
   //layout2->addWidget(ui->volBtn);
    layout2->addWidget(ui->favoriteBtn);
    layout2->addWidget(ui->downloadBtn);
    layout2->addWidget(ui->moreBtn);
    layout2->addWidget(ui->playmoreBtn);
    //layout2->addWidget(m_volButton);
    layout2->addWidget(ui->equalizerBtn);
    layout2->addWidget(ui->lrcBtn);
    layout2->addWidget(ui->playlistBtn);
    layout2->setSpacing(15);
    layout2->setContentsMargins(0, 0, 0, 0);

    QHBoxLayout *bottomLayout = new QHBoxLayout();
    bottomLayout->addLayout(layout1);
    bottomLayout->setSpacing(20);
    bottomLayout->addLayout(vlayout);
    //bottomLayout->addSpacing(30);
    bottomLayout->addLayout(layout3);
    //bottomLayout->setSpacing(10);
    bottomLayout->addLayout(layout2);
    bottomLayout->setContentsMargins(12, 0, 12, 5);
    ui->bottomWidget->setLayout(bottomLayout);
}

void Widget::topWidgetInit()
{
    ui->logoBtn->setStyleSheet("QPushButton{background:transparent;border-image:url(:/image/topwidget/label_icon.png)}");
    ui->loginBtn->setStyleSheet("QPushButton{background:transparent;color:white;font-family:宋体;font-size:12px;}");
    ui->label_3->setText("丨");
    ui->label_3->setStyleSheet("color:white;");
    ui->label_3->adjustSize();
    ui->registerBtn->setStyleSheet("QPushButton{background:transparent;color:white;font-family:宋体;font-size:12px;}");

    QHBoxLayout *layout1 = new QHBoxLayout();
    layout1->addWidget(ui->logoBtn);
    layout1->addSpacing(6);
    layout1->addWidget(ui->loginBtn);
    layout1->addWidget(ui->label_3);
    layout1->addWidget(ui->registerBtn);
    layout1->addSpacing(5);
    layout1->setContentsMargins(0, 0, 0, 0);
    layout1->setSpacing(6);


    ui->returnBtn->setStyleSheet("QPushButton{border-image:url(:/image/topwidget/btn_ return(1).png);}"
                                 "QPushButton::hover{border-image:url(:/image/topwidget/btn_ return(2).png);}"
                                 "QPushButton::pressed{border-image:url(:/image/topwidget/btn_ return(3).png);}");
    ui->refreshBtn->setStyleSheet("QPushButton{border-image:url(:/image/topwidget/btn_refresh(1).png);}"
                                  "QPushButton::hover{border-image:url(:/image/topwidget/btn_refresh(2).png);}"
                                  "QPushButton::pressed{border-image:url(:/image/topwidget/btn_refresh(3).png);}");

    ui->lineEdit->setStyleSheet("QLineEdit{border-radius:13px;background:rgb(255,255,255,180);}");
    ui->lineEdit->setContextMenuPolicy(Qt::NoContextMenu);
    myPushButton *serbtn = new myPushButton(ui->lineEdit);
    serbtn->setFixedSize(16,16);
    serbtn->setStyleSheet("QPushButton{background:transparent;border-image: url(:/image/topwidget/btn_search (1).png);}"
                          "QPushButton::hover{border-image: url(:/image/topwidget/btn_search (2).png);}"
                          "QPushButton::pressed{border-image: url(:/image/topwidget/btn_search (3).png);}");
    ui->lineEdit->setPlaceholderText("冯提莫-佛系少女");
    QMargins margins = ui->lineEdit->textMargins();
    ui->lineEdit->setTextMargins(margins.left() + 15, margins.top(), serbtn->width() + 15, margins.bottom());

    QHBoxLayout *pSearchLayout = new QHBoxLayout();
    pSearchLayout->addStretch();
    pSearchLayout->addWidget(serbtn);
    pSearchLayout->setSpacing(0);
    pSearchLayout->setContentsMargins(0, 0, 15, 0);
    ui->lineEdit->setLayout(pSearchLayout);

    QHBoxLayout *layout2 = new QHBoxLayout();
    layout2->addWidget(ui->returnBtn);
    layout2->addWidget(ui->refreshBtn);
    layout2->addWidget(ui->lineEdit);
    layout2->setSpacing(20);
    layout2->setContentsMargins(0, 0, 0, 0);


    ui->miniBtn->setStyleSheet("QPushButton{border-image:url(:/image/topwidget/btn_mini (1).png);}"
                               "QPushButton::hover{border-image:url(:/image/topwidget/btn_mini (2).png);}"
                               "QPushButton::pressed{border-image:url(:/image/topwidget/btn_mini (3).png);}");
    ui->closeBtn->setStyleSheet("QPushButton{border-image:url(:/image/topwidget/btn_close (1).png);}"
                                "QPushButton::hover{border-image:url(:/image/topwidget/btn_close (2).png);}"
                                "QPushButton::pressed{border-image:url(:/image/topwidget/btn_close (3).png);}");
    ui->miniFrameBtn->setStyleSheet("QPushButton{border-image:url(:/image/topwidget/btn_miniframe (1).png);}"
                                    "QPushButton::hover{border-image:url(:/image/topwidget/btn_miniframe (2).png);}"
                                    "QPushButton::pressed{border-image:url(:/image/topwidget/btn_miniframe (3).png);}");
    ui->mobileBtn->setStyleSheet("QPushButton{border-image:url(:/image/topwidget/btn_mobile (1).png);}"
                                 "QPushButton::hover{border-image:url(:/image/topwidget/btn_mobile (2).png);}"
                                 "QPushButton::pressed{border-image:url(:/image/topwidget/btn_mobile (3).png);}");
    ui->label_2->setText("丨");
    ui->label_2->setStyleSheet("color:rgb(255,255,255,50);");
    ui->label_2->adjustSize();

    ui->setBtn->setStyleSheet("QPushButton{border-image:url(:/image/topwidget/btn_setting (1).png);}"
                              "QPushButton::hover{border-image:url(:/image/topwidget/btn_setting (2).png);}"
                              "QPushButton::pressed{border-image:url(:/image/topwidget/btn_setting (3).png);}");
    ui->skinBtn->setStyleSheet("QPushButton{border-image:url(:/image/topwidget/btn_skin (1).png);}"
                               "QPushButton::hover{border-image:url(:/image/topwidget/btn_skin (2).png);}"
                               "QPushButton::pressed{border-image:url(:/image/topwidget/btn_skin (3).png);}");
    ui->messageBtn->setStyleSheet("QPushButton{border-image:url(:/image/topwidget/btn_message (1).png);}"
                                  "QPushButton::hover{border-image:url(:/image/topwidget/btn_message (2).png);}"
                                  "QPushButton::pressed{border-image:url(:/image/topwidget/btn_message (3).png);}");
    ui->playGameBtn->setStyleSheet("QPushButton{border-image:url(:/image/topwidget/btn_playcard (1).png);}"
                                   "QPushButton::hover{border-image:url(:/image/topwidget/btn_playcard (2).png);}"
                                   "QPushButton::pressed{border-image:url(:/image/topwidget/btn_playcard (3).png);}");
    ui->toolBtn->setStyleSheet("QPushButton{border-image:url(:/image/topwidget/btn_tool (1).png);}"
                               "QPushButton::hover{border-image:url(:/image/topwidget/btn_tool (2).png);}"
                               "QPushButton::pressed{border-image:url(:/image/topwidget/btn_tool (3).png);}");
    ui->gameBtn->setStyleSheet("QPushButton{border-image:url(:/image/topwidget/btn_game (1).png);}"
                               "QPushButton::hover{border-image:url(:/image/topwidget/btn_game (2).png);}"
                                "QPushButton::pressed{border-image:url(:/image/topwidget/btn_game (3).png);}");

    QHBoxLayout *layout3 = new QHBoxLayout();
    layout3->addWidget(ui->toolBtn);
    layout3->addWidget(ui->playGameBtn);
    layout3->addWidget(ui->gameBtn);
    layout3->addWidget(ui->messageBtn);
    layout3->addWidget(ui->skinBtn);
    layout3->addWidget(ui->setBtn);
    layout3->addWidget(ui->label_2);
    layout3->addWidget(ui->mobileBtn);
    layout3->addWidget(ui->miniFrameBtn);
    layout3->addWidget(ui->miniBtn);
    layout3->addWidget(ui->closeBtn);
    layout3->setSpacing(12);

    QHBoxLayout *topLayout = new QHBoxLayout();
    topLayout->addLayout(layout1);
    topLayout->addSpacing(190);
    topLayout->addSpacerItem(new QSpacerItem(80, 30, QSizePolicy::Maximum));
    topLayout->addLayout(layout2);
    //topLayout->addSpacing(20);
    topLayout->addSpacerItem(new QSpacerItem(110, 30, QSizePolicy::Expanding));//膨胀
    topLayout->addLayout(layout3);
    topLayout->setSpacing(0);
    topLayout->setContentsMargins(16, 5, 15, 0);
    ui->topWidget->setLayout(topLayout);
}

void Widget::setSkin(const QString &str)
{
    m_curPix = QPixmap(str);
    m_curPixPath = str;
    update();
}

void Widget::paintEvent(QPaintEvent */*e*/)
{
    //QWidget::paintEvent(e);
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    p.setRenderHints(QPainter::SmoothPixmapTransform, true);//消锯齿

    //double d =(double)m_curPix.height() / m_curPix.width();
   // int h = d * width();
   // int w = height() / d;
   // p.drawPixmap(0, 0, width(), h, m_curPix);
   // m_curPix = m_curPix.scaled(width(), h);
   // if(h < height())//如果图片高度小于窗口高度
   // {
    //    p.drawPixmap(0, 0, w, height(), m_curPix);
    //    m_curPix = m_curPix.scaled(w, height());
   // }
    p.drawPixmap(0, 0, width(), height(), m_curPix);


    QPainter painter(this);
  //  painter.setRenderHint(QPainter::Antialiasing, true);
 //   painter.fillPath(path, QBrush(Qt::white));

    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    path.addRect(m_midWidget->x(), m_midWidget->y(), m_midWidget->width(), m_midWidget->height());
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.fillPath(path, QBrush(Qt::white));
}

void Widget::on_miniBtn_clicked()
{
    showMinimized();
}

void Widget::on_closeBtn_clicked()
{
    if (Qt::Tool == (windowFlags() & Qt::Tool))
    {
        qApp->quit();
    }
    else
    {
       // qDebug() << "close";
       // disconnect(&m_midWidget->m_leftWid.m_stackwid, 0, 0, 0);
        //disconnect(&m_midWidget->m_rightWid.m_stackWid, 0, 0, 0);
        close();
    }
}
