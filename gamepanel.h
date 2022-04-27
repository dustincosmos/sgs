#ifndef GAMEPANEL_H
#define GAMEPANEL_H

#include <QMainWindow>
#include"cardpanel.h"
#include"player.h"
#include"gamecontrol.h"
#include<QMap>
#include<QPushButton>
#include<QLabel>
#include"robotplayhand.h"
#include<QTimer>
#include"countdown.h"
#include"playerlife.h"
#include"messagewidget.h"
#include<QTextEdit>
#include"endscene.h"
QT_BEGIN_NAMESPACE
namespace Ui { class gamepanel; }
QT_END_NAMESPACE

class gamepanel : public QMainWindow
{
    Q_OBJECT

public:
    gamepanel(QWidget *parent = nullptr);
    ~gamepanel();

    void GameControlinit();
    void initCardMap();
    void cropImage(QPixmap& pix, int x, int y, Card& c);
    void initGamescene();
    void initPlayerContext();
    void startdispatchcard();
    void cardMovestep(Player *player,int curPos);
    void gameStatusPrecess(GameControl::GameStatus status);
    void updatePlayerCards(Player* player);
    void sleep(unsigned int ms);

    void onDispatchcard(Player* player);
    void onCardSelect(Qt::MouseButton button);
    void onUsecard();
    void onRobotRound();
    void onUserRound();
    void npcPlayCard(int index);
    void playShan(Player* player);

    void response();
    void tao();
    void wuzhong();
    void guohe();
    void shunshou();
    void nanman();
    void wangjian();

    void hpchange(Player* player,int num);
    void lifeChange();
    void judchange();

    void gameWin();
    CardPanel* getCurrtCard();

private:
    struct PlayerContext
    {
        QRect cardRect;
        QRect playHandRect;
        bool isFrontSide;
        QLabel* info;
        QLabel* roleImg;
        Cards lastCards;
    };

    Ui::gamepanel *ui;

    QPixmap c_background;
    GameControl* c_gct;
    QVector<Player*> c_playerlist;
    QSize c_size;
    QPixmap c_cardbac;
    QMap<CardPanel*,Card> c_cardmap;
    CardPanel* c_basecard;
    CardPanel* c_movecard;
    QPoint c_basecardPos;
    QMap<Player*,PlayerContext> c_playercontext;
    GameControl::GameStatus c_gamestatus;
    QMap<Player*,PlayerContext> c_contextmap;
    QRect c_cardsrect;
    QHash<CardPanel*,QRect> c_userCards;

    QVector<CardPanel*> c_carddeal;  //用于存蓄牌堆
    Cards c_userhand;
    Cards c_robothand;

    QVector<CardPanel*> c_userpanel;
    QVector<CardPanel*> c_robotpanel;

//    QPushButton *playcard;
    QVector<CardPanel*> c_pendcard;

    QTimer* c_timer;
    CountDown* countdown;
    CountDown* xiangying;

    CardPanel *currt_card;

    playerLife *c_userlife;
    playerLife *c_robotlife;

    messageWidget* mess;

    bool jud=1;
    bool nan_jud=1;

    QPushButton *fapai;


protected:
    void paintEvent(QPaintEvent *ev);

signals:
    void onUsesha();
    void onUseshan();
    void onUsetao();
    void onUsewuzhong();
    void onUseguohe();
    void onUseshunshou();
    void onUsenanman();
    void onUsewangjian();
};
#endif // GAMEPANEL_H
