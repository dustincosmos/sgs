#include "player.h"

Player::Player(QObject *parent) : QObject(parent)
{

}

void Player::setIdentify(identify iden)
{
    c_identify = iden;
}

Player::identify Player::getIdentify()
{
    return c_identify;
}

void Player::setPlayerType(playerType type)
{
    c_playertype = type;
}

Player::playerType Player::getPlayerType()
{
    return c_playertype;
}

void Player::storeCard(Card &card)
{
    c_cards.add(card);
}

void Player::storeCard(Cards &cards)
{
    c_cards.add(cards);
}

void Player::setNextPlayer(Player *player)
{
    nextplayer = player;
}

Player* Player::getNextPlayer()
{
    return nextplayer;
}

void Player::setPosition(playerPosition position)
{
    c_position = position;
}

Player::playerPosition Player::getPosition()
{
    return c_position;
}

void Player::clear()
{
    c_cards.clear();
}

void Player::playHand(Card &card)
{
    c_cards.remove(card);
    emit notifyPlayHand(this,c_card);
}

Card Player::getCard()
{
    return c_card;
}

Cards Player::getCards()
{
    return c_cards;
}

void Player::preparePlayhand()
{

}

void Player::thinkPlayhand()
{

}

void Player::round()
{

}
