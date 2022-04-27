#include "cardpanel.h"
#include<QPainter>
#include<QMouseEvent>
#include<QPropertyAnimation>
CardPanel::CardPanel(QWidget *parent) : QWidget(parent)
{

}

void CardPanel::setImage(QPixmap &front, QPixmap &back)
{
    c_front = front;
    c_back = back;

    setFixedSize(c_front.size());
    update();
}

QPixmap CardPanel::getImage()
{
    if(isFront)
        return c_front;
    else
        return c_back;
}

void CardPanel::setFront(int flag)
{
    isFront = flag;
}

bool CardPanel::isFrontSide()
{
    return isFront;
}

void CardPanel::setBack(int flag)
{
    isFront = flag;
}

bool CardPanel::isBackSide()
{
    return isBack;
}

void CardPanel::setSelect(int flag)
{
    is_select = flag;
}

bool CardPanel::isSelect()
{
    return is_select;
}

void CardPanel::setCard(Card &card)
{
    c_card = card;
}

Card CardPanel::getCard()
{
    return c_card;
}

void CardPanel::zoom1()
{
    QPropertyAnimation *ani=new QPropertyAnimation(this,"geometry");
    ani->setDuration(200);

    ani->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));

    ani->setEndValue(QRect(this->x(),this->y()-10,this->width(),this->height()));

    ani->setEasingCurve(QEasingCurve::OutBounce);
    ani->start();

}

void CardPanel::zoom2()
{
    QPropertyAnimation *ani=new QPropertyAnimation(this,"geometry");
    ani->setDuration(200);

    ani->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));

    ani->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));

    ani->setEasingCurve(QEasingCurve::OutBounce);
    ani->start();
}

void CardPanel::setOwner(Player* player)
{
    c_player = player;
}

Player* CardPanel::getOwner()
{
    return c_player;
}

void CardPanel::clicked()
{
    emit cardChoose(Qt::LeftButton);
}

void CardPanel::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter p(this);
    if(isFront)
        p.drawPixmap(rect(),c_front);

    else
        p.drawPixmap(rect(),c_back);

}

void CardPanel::mousePressEvent(QMouseEvent *event)
{
    emit cardChoose(event->button());
//    if(event->buttons() & Qt::LeftButton )
//    {
//        this->zoom1();
//       this->zoom2();
//    }
//    if(event->buttons() & Qt::RightButton)
//    {
//        this->zoom2();
//    }
}
