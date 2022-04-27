#ifndef CARDS_H
#define CARDS_H
#include"card.h"
#include<QSet>
class Cards
{
public:
    Cards();
    Cards(Card &card);

    void add(Card &card);
    void add(Cards &cards);

    void remove(Card &card);
    void remove(Cards &cards);

    int cardCount();
    bool isEmpty();
    bool contain(Card &card);
    void clear();

    Card takeCard();
    CardList toCardList();

private:

    QSet<Card> c_cards;
};


#endif // CARDS_H
