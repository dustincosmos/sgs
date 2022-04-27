#ifndef CARDPANEL_H
#define CARDPANEL_H

#include <QWidget>
#include"card.h"
#include"player.h"
class CardPanel : public QWidget
{
    Q_OBJECT
public:
    explicit CardPanel(QWidget *parent = nullptr);

    void setImage(QPixmap &front,QPixmap &back);
    QPixmap getImage();

    void setFront(int flag);
    bool isFrontSide();

    void setBack(int flag);
    bool isBackSide();

    void setSelect(int flag);
    bool isSelect();

    void setCard(Card &card);
    Card getCard();

    void zoom1();
    void zoom2();

    void setOwner(Player* player);
    Player* getOwner();

    void clicked();

signals:
    void cardChoose(Qt::MouseButton button);

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);

private:
    QPixmap c_front;
    QPixmap c_back;

    bool isFront;
    bool isBack;

    bool is_select;
    Card c_card;

    Player* c_player;
};

#endif // CARDPANEL_H
