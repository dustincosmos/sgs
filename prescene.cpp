#include "prescene.h"
#include<QPainter>
#include"gamepanel.h"
#include<QDebug>
PreScene::PreScene(QWidget *parent) : QMainWindow(parent)
{
    this->resize(1000,650);
    this->setWindowTitle("三国杀");

    startbtn = new QPushButton(this);
    setbtn = new QPushButton(this);
    QPushButton *helpbtn= new QPushButton(this);
    QPushButton *quitbtn= new QPushButton(this);



//    helpbtn = new QPushButton(this);
//    quitbtn = new QPushButton(this);

    startbtn->move((rect().width()-startbtn->width())/2,(rect().height()-startbtn->height())/2-75);
    setbtn->move((rect().width()-setbtn->width())/2,(rect().height()-setbtn->height())/2-25);
    helpbtn->move((rect().width()-helpbtn->width())/2,(rect().height()-helpbtn->height())/2+25);
    quitbtn->move((rect().width()-quitbtn->width())/2,(rect().height()-quitbtn->height())/2+75);

//    qDebug()<<startbtn->x()<<startbtn->y();

    startbtn->setText("开始游戏");
    setbtn->setText("游戏设置");
    helpbtn->setText("帮助");
    quitbtn->setText("退出游戏");


    gamepanel* gp = new gamepanel;
    connect(startbtn,&QPushButton::clicked,[=]()
    {
        this->hide();
        gp->show();
    });
}

void PreScene::paintEvent(QPaintEvent *ev)
{
    Q_UNUSED(ev);
    QPainter p(this);
    QPixmap pix(":/img/prescene.png");
    p.drawPixmap(rect(),pix);

}
