#include "robotplayhand.h"
#include"gamepanel.h"
RobotPlayHand::RobotPlayHand(Player* player,QObject *parent) : QThread(parent)
{
    c_player = player;
}

void RobotPlayHand::run()
{
    c_player->thinkPlayhand();
    msleep(2000);
}

RobotRound::RobotRound(Player *player, QObject *parent) : QThread(parent)
{
    c_player = player;
}

void RobotRound::run()
{
    c_player->round();    
    msleep(2000);
}
