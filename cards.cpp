#include "cards.h"
#include<QRandomGenerator>
#include<QSet>
Cards::Cards()
{

}

Cards::Cards(Card &card)
{
    add(card);
}

void Cards::add(Card &card)
{
    c_cards.insert(card);
}

void Cards::add(Cards &cards)
{
    c_cards.unite(cards.c_cards);
}

void Cards::remove(Card &card)
{
    c_cards.remove(card);
}

void Cards::remove(Cards &cards)
{
    c_cards.subtract(cards.c_cards);
}

int Cards::cardCount()
{
    return c_cards.size();
}

bool Cards::isEmpty()
{
    if(!cardCount())
        return true;
    return false;
}

bool Cards::contain(Card &card)
{
    return c_cards.contains(card);
}

void Cards::clear()
{
    c_cards.clear();
}

Card Cards::takeCard()
{
    int num = QRandomGenerator::global()->bounded(c_cards.size());
    QSet<Card>::const_iterator it = c_cards.constBegin();
    for(int i=0;i<num;i++,it++);
    Card card = *it;
    c_cards.erase(it);
    return card;
}

CardList Cards::toCardList()
{
    CardList list;
    for(auto it=c_cards.begin();it!=c_cards.end();it++)
        list<<*it;
    return list;
}
