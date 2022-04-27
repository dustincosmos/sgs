#ifndef GAMECONTROL_H
#define GAMECONTROL_H

#include <QObject>
#include"robot.h"
#include"userplayer.h"
class GameControl : public QObject
{
    Q_OBJECT
public:
    enum GameStatus
    {
        deal,//发牌
        playHand//出牌
    };

    enum PlayerStatus
    {
        thinkPlay,
//        prepare,//准备阶段
//        judge,//判断阶段
        touch_cards,//摸牌阶段
        discard,//弃牌阶段
        isWin
    };

    explicit GameControl(QObject *parent = nullptr);

    void playerInit();

    Robot* getRobotPlayer();
    UserPlayer* getUserPlayer();

    void setCurrentplayer(Player *player);
    Player* getCurrentPlayer();

    void setobjPlayer(Player* player);
    Player* getobjPlayer();

    Card takeOnecard();

    void initCards();




private:

    Robot *c_robot = nullptr;
    UserPlayer *c_user = nullptr;

    Player *c_player = nullptr;
    Player* obj_player;
    Cards *c_allcards ;

signals:
    void playerStatusChanged(Player* player, PlayerStatus status);
    void gameStatusChanged(GameStatus status);
    void notifyPlayHand(Player* player, const Cards& card);
    void pendingInfo(Player* player, const Cards& card);


};

#endif // GAMECONTROL_H
