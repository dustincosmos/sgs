#ifndef USERPLAYER_H
#define USERPLAYER_H

#include <player.h>
#include <QObject>

class UserPlayer : public Player
{
    Q_OBJECT
public:
    explicit UserPlayer(QObject *parent = nullptr);

    void preparePlayhand() override;
    void thinkPlayhand() override;
};

#endif // USERPLAYER_H
