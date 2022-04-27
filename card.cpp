#include "card.h"

Card::Card()
{

}

Card::Card(CardType type)
{
    setType(type);
}

Card::Card(CardType type, CardPoint point)
{
    setPoint(point);
    setType(type);
}

Card::Card(CardPoint point,CardSuit suit)
{
    setPoint(point);
    setSuit(suit);

}

void Card::setPoint(CardPoint Point)
{
    c_point = Point;
}

void Card::setSuit(CardSuit Suit)
{
    c_suit = Suit;
}

void Card::setType(CardType type)
{
    c_type = type;
}

Card::CardPoint Card::Point() const
{
    return c_point;
}

Card::CardSuit Card::Suit() const
{
    return c_suit;
}

Card::CardType Card::Type() const
{
    return c_type;
}

bool operator < (const Card &c1,const Card &c2)
{
    return c1.Type()<c2.Type();
}

bool operator ==(const Card &left,const Card &right)
{
    return (left.Point() == right.Point() && (left.Suit() == right.Suit()));
}

uint qHash(const Card &card)
{
    return card.Point()*100+card.Suit();
}
