#include "countdown.h"
#include<QPainter>
CountDown::CountDown(QWidget *parent) : QWidget(parent)
{

    c_1.load(":/num/1.png");
    c_2.load(":/num/2.png");
    c_3.load(":/num/3.png");
    c_4.load(":/num/4.png");
    c_5.load(":/num/5.png");
    c_timer =new QTimer(this);
    connect(c_timer,&QTimer::timeout,this,[=](){
       count--;
       if(count <= 0)
       {
           c_timer->stop();
           emit timeout();
       }
    });
}

void CountDown::showCountDown()
{
    count=5;
    c_timer->start(1000);
}

void CountDown::npcCountdown()
{
    count=3;
    c_timer->start(1000);
}

void CountDown::paintEvent(QPaintEvent *ev)
{
    Q_UNUSED(ev);
    QPainter p(this);
    p.drawPixmap(rect(),c_time);
}
