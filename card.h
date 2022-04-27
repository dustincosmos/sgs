#ifndef CARD_H
#define CARD_H
#include<QVector>

class Card
{
public:

    enum CardSuit
    {
        Diamond,
        Club,
        Heart,
        Spade
    };

    enum CardPoint
    {
        Card_1,
        Card_2,
        Card_3,
        Card_4,
        Card_5,
        Card_6,
        Card_7,
        Card_8,
        Card_9,
        Card_10,
        Card_j,
        Card_q,
        Card_k
    };

    enum CardType
    {
        sha,
        shan,
        tao,
        wuzhongshengyou,
        guohecaiqiao,
        nanmanruqin,
        wangjianqifa,
        shunshouqianyang
    };

    Card();
    Card(CardType type);
    Card(CardType type,CardPoint point);
    Card(CardPoint Point,CardSuit Suit);

    void setPoint(CardPoint Point);
    void setSuit(CardSuit Suit);
    void setType(CardType type);

    CardPoint Point() const;
    CardSuit Suit() const;
    CardType Type() const;

private:
    CardPoint c_point;
    CardSuit c_suit;
    CardType c_type;
};

bool operator < (const Card &c1,const Card &c2);
bool operator == (const Card &left,const Card &right);
uint qHash(const Card &card);

using CardList = QVector<Card>;

#endif // CARD_H
