#include "robot.h"
#include<QDebug>
Robot::Robot(QObject *parent) : Player(parent)
{
    c_playertype = Player::robot;
}

void Robot::preparePlayhand()
{

}

void Robot::thinkPlayhand()
{
    qDebug()<<"进入进程"<<endl;
//    emit onUseShan(this);
    emit preround();
}

void Robot::round()
{
    qDebug()<<"npc回合"<<endl;
    emit Round();
}
