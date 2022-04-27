#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include"cards.h"

class Player : public QObject
{
    Q_OBJECT
public:

    enum identify
    {
        lord,//主公
        loyal,//忠臣
        rebel,//反贼
        traitor//内奸
    };

    enum playerType
    {
        robot,
        user
    };

    enum playerPosition
    {
        Mid,
        unMid
    };

    explicit Player(QObject *parent = nullptr);

    void setIdentify(identify iden);
    identify getIdentify();

    void setPlayerType(playerType type);
    playerType getPlayerType();

    void storeCard(Card &card);
    void storeCard(Cards &cards);

    void setNextPlayer(Player *player);
    Player* getNextPlayer();

    void setPosition(playerPosition position);
    playerPosition getPosition();

    void clear();
    void playHand(Card &card);
    Card getCard();
    Cards getCards();

    virtual void preparePlayhand();
    virtual void thinkPlayhand();
    virtual void round();

protected:
    identify c_identify;
    playerType c_playertype;
    playerPosition c_position;

    Cards c_cards;
    Card c_card;

    Player *nextplayer;
signals:

    void onUseShan(Player *player);
    void preround();
    void notifyPlayHand(Player* player,Card card);
    void Round();
};

#endif // PLAYER_H
