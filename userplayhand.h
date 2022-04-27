#ifndef USERPLAYHAND_H
#define USERPLAYHAND_H

#include <QObject>
#include<QThread>
#include"userplayer.h"
class userPlayhand : public QThread
{
    Q_OBJECT
public:
    explicit userPlayhand(Player* player,QObject *parent = nullptr);

protected:
    void run() override;

private:
    Player *c_player;
signals:

};

#endif // USERPLAYHAND_H
