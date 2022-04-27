#ifndef ROBOTPLAYHAND_H
#define ROBOTPLAYHAND_H

#include <QThread>
#include"player.h"
class RobotPlayHand : public QThread
{
    Q_OBJECT
public:
    explicit RobotPlayHand(Player* player, QObject *parent = nullptr);

signals:

protected:
    void run() override;

private:
    Player* c_player;

};

class RobotRound : public QThread
{
    Q_OBJECT
public:
    explicit RobotRound(Player* player, QObject *parent = nullptr);

signals:

protected:
    void run() override;

private:
    Player* c_player;

};

#endif // ROBOTPLAYHAND_H
