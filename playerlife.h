#ifndef PLAYERLIFE_H
#define PLAYERLIFE_H

#include <QWidget>
#include<QPainter>
#include<QPixmap>
#include"player.h"
class playerLife : public QWidget
{
    Q_OBJECT
public:
    explicit playerLife(Player* player, QWidget *parent = nullptr);
    void setLife(int l);
    void setOwner(Player *player);
protected:
    void paintEvent(QPaintEvent *ev);
private:
    QPixmap c_life;
    QPixmap c_0;
    QPixmap c_1;
    QPixmap c_2;
    QPixmap c_3;
    QPixmap c_4;
    Player* obj_player;
signals:
    void healReduce();

};

#endif // PLAYERLIFE_H
