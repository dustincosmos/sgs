#include "userplayer.h"
#include<QDebug>
UserPlayer::UserPlayer(QObject *parent) : Player(parent)
{
    c_playertype = Player::user;
}

void UserPlayer::preparePlayhand()
{

}

void UserPlayer::thinkPlayhand()
{
    qDebug()<<"进入响应进程"<<endl;
}
