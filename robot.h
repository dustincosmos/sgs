#ifndef ROBOT_H
#define ROBOT_H

#include <player.h>
#include <QObject>

class Robot : public Player
{
    Q_OBJECT
public:
    using Player::Player;
    explicit Robot(QObject *parent = nullptr);

    void preparePlayhand() override;
    void thinkPlayhand() override;
    void round() override;
};

#endif // ROBOT_H
