#include "gamecontrol.h"
#include<QRandomGenerator>


GameControl::GameControl(QObject *parent) : QObject(parent)
{

}

void GameControl::playerInit()
{
    c_user = new UserPlayer(this);
    c_robot = new Robot(this);

    c_user->setNextPlayer(c_robot);
    c_robot->setNextPlayer(c_user);

    c_user->setPosition(Player::Mid);
    c_robot->setPosition(Player::unMid);

    c_player = c_user;
}

Robot *GameControl::getRobotPlayer()
{
    return c_robot;
}

UserPlayer* GameControl::getUserPlayer()
{
    return c_user;
}

void GameControl::setCurrentplayer(Player *player)
{
    c_player = player;
}

Player *GameControl::getCurrentPlayer()
{
    return c_player;
}

void GameControl::setobjPlayer(Player *player)
{
    obj_player = player;
}

Player* GameControl::getobjPlayer()
{
    return obj_player;
}

Card GameControl::takeOnecard()
{
    return c_allcards->takeCard();
}

void GameControl::initCards()
{
    for(int i=Card::sha;i<=Card::shan;i++)
    {
        for(int j=0;j<20;j++)
        {
            Card c((Card::CardType)i);
            c_allcards->add(c);
        }
    }
}

