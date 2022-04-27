#include "userplayhand.h"

userPlayhand::userPlayhand(Player* player,QObject *parent) : QThread(parent)
{
    c_player = player;
}

void userPlayhand::run()
{
    c_player->thinkPlayhand();
}
