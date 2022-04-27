#include "endscene.h"
#include<QPainter>
#include<QPixmap>
endScene::endScene(QWidget *parent) : QWidget(parent)
{
    this->show();
    this->setFixedSize(500,500);
}

void endScene::setWinner(bool f)
{
    flag = f;
}

void endScene::paintEvent(QPaintEvent *ev)
{
    Q_UNUSED(ev);
    QPainter p(this);
    QPixmap pix;
    if(flag)
        pix.load(":/img/wg.png");
    else
        pix.load(":/img/fal.png");
    p.drawPixmap(rect(),pix);
}
