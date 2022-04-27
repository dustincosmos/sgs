#include "playerlife.h"

playerLife::playerLife(Player* player, QWidget *parent) : QWidget(parent)
{
    setOwner(player);
    c_0.load(":/img/zero_xue.png");
    c_1.load(":/img/one_xue.png");
    c_2.load(":/img/two_xue.png");
    c_3.load(":/img/three_xue.png");
    c_4.load(":/img/four_xue.png");
    setLife(4);
}


void playerLife::setLife(int l)
{
    if (l == 0)
        c_life = c_0;
    else if (l == 1)
        c_life = c_1;
    else if (l == 2)
        c_life = c_2;
    else if (l == 3)
        c_life = c_3;
    else if (l == 4)
        c_life = c_4;
    emit healReduce();
    setFixedSize(c_life.size());
    update();
}

void playerLife::setOwner(Player *player)
{
    obj_player = player;
}

void playerLife::paintEvent(QPaintEvent *ev)
{
    Q_UNUSED(ev);
    QPainter p(this);
    p.drawPixmap(rect(),c_life);
}
