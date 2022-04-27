#include "gamepanel.h"
#include "ui_gamepanel.h"
#include"player.h"
#include<QPainter>
#include<QDebug>
#include<QRandomGenerator>
#include<QTimer>
#include"userplayhand.h"
#include<QCoreApplication>
#include<QApplication>
#include<QTime>
static int robot_life = 4;
static int user_life = 4;

gamepanel::gamepanel(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::gamepanel)
{
    ui->setupUi(this);
    c_background.load(":/img/gamescene.png");
    c_cardbac.load(":/img/cardbac.png");
    this->setWindowTitle("三国杀");
    this->setFixedSize(1000,650);

    currt_card = new CardPanel(this);

    GameControlinit();
    initCardMap();
    initPlayerContext();
    initGamescene();
//    onUserRound();

    QPushButton *playcard = new QPushButton(this);
    QPushButton *cancel = new QPushButton(this);
    fapai =new QPushButton(this);
    QPushButton *endbtn = new QPushButton(this);
    QPushButton *rob = new QPushButton(this);

    c_timer = new QTimer(this);
    countdown = new CountDown(this);
    xiangying = new CountDown(this);

    mess = new messageWidget(this);
    mess->move(rect().width()-mess->width(),rect().height()/2-mess->height()/2);
//    mess->setFixedSize(200,200);

    playcard->setText("出牌");
    cancel->setText("取消");
    fapai->setText("开始发牌");
    endbtn->setText("回合结束");
    rob->setText("npc");

    rob->hide();

    playcard->move(370,470);
    cancel->move(500,470);
    fapai->move((rect().width()-fapai->width())/2,360);
    endbtn->move(800,470);

    CardPanel* role1 = new CardPanel(this);
    CardPanel* role2 = new CardPanel(this);

    QPixmap pix1(":/img/zhangfei.png");
    QPixmap pix2(":/img/zhangfei.png");

    role1->setImage(pix1,pix1);
    role2->setImage(pix2,pix2);

    rob->move(10,50);
    role1->move(0,rect().height()-pix1.height());
    role2->move(rect().width()-pix1.width(),0);

    c_userlife = new playerLife(c_gct->getUserPlayer(), this);
    c_robotlife = new playerLife(c_gct->getUserPlayer(), this);

    c_userlife->move(pix1.width(),rect().height()-pix1.height());
    c_robotlife->move(rect().width()-pix1.width()-30,0);


    connect(fapai,&QPushButton::clicked,this,&gamepanel::startdispatchcard);
    connect(fapai,&QPushButton::clicked,this,&gamepanel::onUserRound);
    connect(playcard,&QPushButton::clicked,this,&gamepanel::onUsecard);
    connect(c_gct->getRobotPlayer(),&Player::onUseShan,this,&gamepanel::playShan);
    connect(endbtn,&QPushButton::clicked,this,&gamepanel::onRobotRound);

    connect(countdown,&CountDown::timeout,this,&gamepanel::onUserRound);
    connect(this,&gamepanel::onUsesha,this,&gamepanel::response);

    connect(this,&gamepanel::onUseshan,this,&gamepanel::judchange);
    connect(this,&gamepanel::onUsesha,this,&gamepanel::judchange);

    connect(this,&gamepanel::onUsewuzhong,this,&gamepanel::wuzhong);
    connect(this,&gamepanel::onUseguohe,this,&gamepanel::guohe);
    connect(this,&gamepanel::onUseshunshou,this,&gamepanel::shunshou);
    connect(this,&gamepanel::onUsenanman,this,&gamepanel::nanman);
    connect(this,&gamepanel::onUsewangjian,this,&gamepanel::wangjian);
    connect(this,&gamepanel::onUsetao,this,&gamepanel::tao);

    connect(xiangying,&CountDown::timeout,this,&gamepanel::lifeChange);


    connect(c_robotlife,&playerLife::healReduce,this,&gamepanel::gameWin);
    connect(c_userlife,&playerLife::healReduce,this,&gamepanel::gameWin);
}

gamepanel::~gamepanel()
{
    delete ui;
}

void gamepanel::GameControlinit()
{
    c_gct = new GameControl(this);
    c_gct->playerInit();

    Robot *c_robot = c_gct->getRobotPlayer();
    UserPlayer *c_user = c_gct->getUserPlayer();

    c_playerlist<<c_user<<c_robot;


}

void gamepanel::initCardMap()
{
    QPixmap pix1(":/img/sha.png");
    QPixmap pix2(":/img/shan.png");
    QPixmap pix3(":/img/peach.png");
    QPixmap pix4(":/img/wuzhong.png");
    QPixmap pix5(":/img/guohe.png");
    QPixmap pix6(":/img/nanman.png");
    QPixmap pix7(":/img/wangjian.png");
    QPixmap pix8(":/img/shunshou.png");
    c_size.setWidth(93);
    c_size.setHeight(130);
    for(int i=0, point = Card::Card_1 ; point<=Card::Card_k; ++point, ++i)
    {
        for(int j=0,type=Card::sha; type<=Card::shunshouqianyang; ++j,type++)
        {
            Card card((Card::CardType)type,(Card::CardPoint)point);
            if(type == Card::sha)
            {
                cropImage(pix1, j*c_size.width(), i*c_size.height(), card);
            }
            else if(type == Card::shan)
            {
                cropImage(pix2, j*c_size.width(), i*c_size.height(), card);
            }
            else if (type == Card::tao)
            {
                cropImage(pix3, j*c_size.width(), i*c_size.height(), card);
            }
            else if (type == Card::wuzhongshengyou)
            {
                cropImage(pix4, j*c_size.width(), i*c_size.height(), card);
            }
            else if (type == Card::guohecaiqiao)
            {
                cropImage(pix5, j*c_size.width(), i*c_size.height(), card);
            }
            else if (type == Card::nanmanruqin)
            {
                cropImage(pix6, j*c_size.width(), i*c_size.height(), card);
            }
            else if (type == Card::wangjianqifa)
            {
                cropImage(pix7, j*c_size.width(), i*c_size.height(), card);
            }
            else if (type == Card::shunshouqianyang)
            {
                cropImage(pix8, j*c_size.width(), i*c_size.height(), card);
            }
        }
    }

}

void gamepanel::cropImage(QPixmap &pix, int x, int y, Card& c)
{
    QPixmap sub = pix.copy(x, y, c_size.width(), c_size.height());
    CardPanel* panel = new CardPanel(this);
    panel->setImage(sub, c_cardbac);
    panel->setCard(c);
    panel->hide();
    c_cardmap.insert(panel, c);
    connect(panel,&CardPanel::cardChoose,this,&gamepanel::onCardSelect);

    c_carddeal.append(panel);
}

void gamepanel::initGamescene()
{
    c_gct->setCurrentplayer(c_gct->getUserPlayer());
    c_basecard = new CardPanel(this);
    c_basecard->setImage(c_cardbac, c_cardbac);
    c_movecard = new CardPanel(this);
    c_movecard->setImage(c_cardbac, c_cardbac);


    c_basecardPos = QPoint((width() - c_size.width()) / 2,height() / 2 - 100);
    c_basecard->move(c_basecardPos);
    c_movecard->move(c_basecardPos);

}

void gamepanel::initPlayerContext()
{
    QPainter p(this);
    const QRect cardsRect[] =
    {
        QRect(250, rect().top() + 120, width() - 500, 150),
        QRect(250, rect().bottom() - 120, width() - 500, 150)
    };
    QPixmap pix(":/img/background.png");
    p.drawPixmap(cardsRect[0],pix);
    const QRect playHandRect[] =
    {
        QRect(150, rect().top() + 290, width() - 300, 150),
        QRect(150, rect().bottom() - 290, width() - 300, 150)
    };
    const QPoint roleImgPos[] =
    {
        QPoint(cardsRect[0].left()-80, cardsRect[0].height() / 2 + 20),
        QPoint(cardsRect[1].right()+10, cardsRect[1].height() / 2 + 20)
    };

    int index = c_playerlist.indexOf(c_gct->getUserPlayer());
    for(int i=0; i<c_playerlist.size(); ++i)
    {
        PlayerContext context;
        context.isFrontSide = i==index ? true : false;
        context.cardRect = cardsRect[i];
        context.playHandRect = playHandRect[i];
        context.info = new QLabel(this);
        context.info->resize(160, 98);
        context.info->hide();
        QRect rect = playHandRect[i];
        QPoint pt(rect.left() + (rect.width() - context.info->width()) / 2,
                  rect.top() + (rect.height() - context.info->height()) / 2);
        context.info->move(pt);
        context.roleImg = new QLabel(this);
        context.roleImg->resize(84, 120);
        context.roleImg->hide();
        context.roleImg->move(roleImgPos[i]);
        c_playercontext.insert(c_playerlist.at(i), context);
    }
}

void gamepanel::startdispatchcard()
{

    for(int i=0;i<4;i++)
    {
        c_carddeal.front()->move((rect().width()-4*c_size.width())/2+i*93,rect().bottom()-130);
        c_carddeal.front()->show();
        c_carddeal.front()->setFront(true);
        c_userhand.add(c_cardmap[c_carddeal.front()]);
        c_userpanel.append(c_carddeal.front());
        c_carddeal.pop_front();

    }
    for(int i=0;i<4;i++)
    {
        c_carddeal.front()->move((rect().width()-4*c_size.width())/2+i*93,rect().top());
        c_carddeal.front()->show();
        c_carddeal.front()->setFront(false);
        c_robothand.add(c_cardmap[c_carddeal.front()]);
        c_robotpanel.append(c_carddeal.front());
        c_carddeal.pop_front();
    }
    fapai->hide();

}

void gamepanel::cardMovestep(Player *player, int curPos)
{
    QRect cardRect = c_playercontext[player].cardRect;

    const int unit[] = {
        (cardRect.top() - c_basecardPos.y()) / 100,
        (cardRect.bottom() - c_basecardPos.y()) / 100
    };
    QPoint pos[] =
    {
        QPoint(c_basecardPos.x(), c_basecardPos.y() + curPos * unit[0]),
        QPoint(c_basecardPos.x(), c_basecardPos.y() - curPos * unit[1]),
    };

    int index = c_playerlist.indexOf(player);
    c_movecard->move(pos[index]);

    if(curPos == 0)
    {
        c_movecard->show();
        qDebug()<<"图片显示"<<endl;
    }
    if(curPos == 100)
    {
        c_movecard->hide();
    }
}

void gamepanel::gameStatusPrecess(GameControl::GameStatus status)
{
    status = GameControl::deal;
    c_gamestatus = status;
    switch(status)
    {
    case GameControl::deal:
        startdispatchcard();
        break;
    default:
        break;
    }
}

void gamepanel::updatePlayerCards(Player *player)
{
    if(player == c_playerlist.at(0))
    {
        for(int i=0;i<c_userpanel.size();i++)
        {
            c_userpanel.at(i)->move((rect().width()-4*c_size.width())/2+i*93,rect().bottom()-130);
        }
    }

    else
    {
        for(int i=0;i<c_robotpanel.size();i++)
        {
            c_robotpanel.at(i)->move((rect().width()-4*c_size.width())/2+i*93,rect().top());
        }
    }
}

void gamepanel::sleep(unsigned int ms)
{
    QTime reachtime = QTime::currentTime().addMSecs(ms);
    while(reachtime > QTime::currentTime())
        QCoreApplication::processEvents(QEventLoop::AllEvents,100);
}


void gamepanel::onDispatchcard(Player* player)//每回合惯例抽卡
{
//    static int curMovePos = 0;
//    int count=0;
//    Player* curPlayer = c_gct->getCurrentPlayer();
//    if(curMovePos >= 100)
//    {
//        Card card = c_gct->takeOnecard();
//        curPlayer->storeCard(card);
//        Cards cs(card);
//        c_gct->setCurrentplayer(curPlayer->getNextPlayer());
//        curMovePos = 0;
//        cardMovestep(curPlayer, curMovePos),count++;
//        if(count==8)
//            return;
//    }
//    cardMovestep(curPlayer, curMovePos),count++;
//    curMovePos += 15;
    player = c_gct->getCurrentPlayer();
    if(player == c_gct->getUserPlayer())
    {
        int t=c_userhand.cardCount();
        for(int i=t;i<t+2;i++)
        {
            c_carddeal.front()->move((rect().width()-4*c_size.width())/2+i*93,rect().bottom()-130);
            c_carddeal.front()->show();
            c_carddeal.front()->setFront(true);
            c_userhand.add(c_cardmap[c_carddeal.front()]);
            c_userpanel.append(c_carddeal.front());
            c_carddeal.pop_front();
        }
        updatePlayerCards(c_gct->getUserPlayer());
    }
    else
    {
        int t=c_robothand.cardCount();
        for(int i=t;i<t+2;i++)
        {
            c_carddeal.front()->move((rect().width()-4*c_size.width())/2+i*93,rect().bottom()-130);
            c_carddeal.front()->show();
            c_carddeal.front()->setFront(false);
            c_robothand.add(c_cardmap[c_carddeal.front()]);
            c_robotpanel.append(c_carddeal.front());
            c_carddeal.pop_front();
        }
        updatePlayerCards(c_gct->getRobotPlayer());
    }

}

void gamepanel::onCardSelect(Qt::MouseButton button)
{
    CardPanel *panel = static_cast<CardPanel*>(sender());
    if(button == Qt::LeftButton)
    {
        panel->setSelect(true);
//        c_pendcard<<panel;
        currt_card = panel;
//        c_userpanel.pop_front();
//        qDebug()<<c_pendcard.size();
        panel->zoom1();
    }
    if(button == Qt::RightButton)
    {
        panel->setSelect(false);
        panel->zoom2();
    }

}

void gamepanel::onUsecard()//判断使用了什么牌
{
    Card tem_c;
//    CardPanel *panel = c_pendcard.front();
    CardPanel *panel = getCurrtCard();
    panel->show();
    panel->setSelect(true);
    if(panel->isSelect())
    {

        for(int i=0;i<c_userpanel.size();i++)
        {
            if(c_userpanel[i]==panel)
            {
                c_userpanel.erase(c_userpanel.begin()+i);
                break;
            }

        }
        panel->move((width() - c_size.width()) / 2+100,height() / 2 - 100);
        qDebug()<<"手牌余量"<<":"<<c_userpanel.size()<<endl;
        updatePlayerCards(c_gct->getUserPlayer());

    }
    for(auto it =c_cardmap.begin();it!=c_cardmap.end();it++)
        if(it.key()==panel)
        {
            tem_c = it.value();
            break;
        }
    if(tem_c.Type()==Card::sha)
    {
        mess->MOUT("玩家打出了杀");
        emit onUsesha();
    }
    else if(tem_c.Type()==Card::shan)
    {
        mess->MOUT("玩家打出了闪");
        emit onUseshan();
    }
    else if (tem_c.Type()==Card::tao)
    {
        mess->MOUT("玩家打出了桃");
        emit onUsetao();
    }
    else if (tem_c.Type()==Card::wuzhongshengyou)
    {
        mess->MOUT("玩家打出了无中生有");
        emit onUsewuzhong();
    }
    else if (tem_c.Type()==Card::guohecaiqiao)
    {
        mess->MOUT("玩家打出了过河拆桥");
        emit onUseguohe();
    }
    else if (tem_c.Type()==Card::shunshouqianyang)
    {
        mess->MOUT("玩家打出了顺手牵羊");
        emit onUseshunshou();
    }
    else if (tem_c.Type()==Card::nanmanruqin)
    {
        mess->MOUT("玩家打出了南蛮入侵");
        emit onUsenanman();
    }
    else if (tem_c.Type()==Card::wangjianqifa)
    {
        mess->MOUT("玩家打出了万箭齐发");
        emit onUsenanman();
    }
    else if (tem_c.Type()==Card::tao)
    {
        mess->MOUT("玩家打出了桃");
        emit onUsetao();
    }
}


void gamepanel::onRobotRound()
{
    mess->MOUT("NPC回合:");
    c_gct->setobjPlayer(c_gct->getUserPlayer());
    c_gct->setCurrentplayer(c_gct->getRobotPlayer());
    countdown->showCountDown();
    RobotRound* sub = new RobotRound(c_playerlist.at(1));
    sub->start();
    onDispatchcard(c_gct->getCurrentPlayer());
    bool sha_num=1;
    for(int i=0;i<c_robotpanel.size();i++)
    {
        if(c_cardmap[c_robotpanel[i]].Type()==Card::wuzhongshengyou)
        {
            npcPlayCard(i);
            mess->MOUT("NPC打出了无中生有");
            onDispatchcard(c_gct->getCurrentPlayer());
            i=0;
        }
        else if(c_cardmap[c_robotpanel[i]].Type()==Card::shunshouqianyang)
        {
            npcPlayCard(i);
            mess->MOUT("NPC打出了顺手牵羊");
            emit onUseshunshou();
            i=0;
        }
        else if(c_cardmap[c_robotpanel[i]].Type()==Card::guohecaiqiao)
        {
            npcPlayCard(i);
            mess->MOUT("NPC打出了过河拆桥");
            emit onUseguohe();
        }
        else if(c_cardmap[c_robotpanel[i]].Type()==Card::sha && sha_num)
        {
            npcPlayCard(i);
            mess->MOUT("NPC打出了杀");
            emit onUsesha();
            sha_num = false;
        }
        else if (c_cardmap[c_robotpanel[i]].Type()==Card::nanmanruqin)
        {
            npcPlayCard(i);
            mess->MOUT("NPC打出了南蛮入侵");
            emit onUsenanman();
            updatePlayerCards(c_gct->getRobotPlayer());
        }
        else if (c_cardmap[c_robotpanel[i]].Type()==Card::wangjianqifa)
        {
            npcPlayCard(i);
            mess->MOUT("NPC打出了万箭齐发");
            emit onUsewangjian();
//            sleep(3000);
            updatePlayerCards(c_gct->getRobotPlayer());
        }
        else if (c_cardmap[c_robotpanel[i]].Type()==Card::tao && robot_life<4)
        {
            npcPlayCard(i);
            mess->MOUT("NPC打出了桃");
            emit onUsetao();
        }
        updatePlayerCards(c_gct->getRobotPlayer());
    }

}

void gamepanel::onUserRound()
{
    mess->MOUT("玩家回合开始");
    c_gct->setobjPlayer(c_gct->getRobotPlayer());
    c_gct->setCurrentplayer(c_gct->getUserPlayer());
    jud=1;
    onDispatchcard(c_gct->getCurrentPlayer());
    updatePlayerCards(c_gct->getUserPlayer());
}

void gamepanel::npcPlayCard(int index)
{
    CardPanel *panel = new CardPanel(this);
    panel = c_robotpanel[index];
    c_robotpanel.erase(index+c_robotpanel.begin());
    panel->setFront(true);
    panel->move((width() - c_size.width()) / 2-100,height() / 2 - 100);
    updatePlayerCards(c_gct->getRobotPlayer());
}

void gamepanel::playShan(Player *player)
{
    Q_UNUSED(player);
    qDebug()<<"num:"<<c_robotpanel.size()<<endl;
    for(int i=0;i<c_robotpanel.size();i++)
        if(c_robothand.contain(c_cardmap[c_robotpanel[i]]))
        {
            c_robotpanel[i]->setFront(true);
            c_robotpanel[i]->move((width() - c_size.width()) / 2-100,height() / 2 - 100);
            c_robothand.remove(c_cardmap[c_robotpanel[i]]);
            break;
        }
    qDebug()<<"出了闪";
}

void gamepanel::response()
{
    Player* player = c_gct->getobjPlayer();
    if(player == c_playerlist.at(1))
    {
        bool judge=1;//1表示未出闪
        for(int i=0;i<c_robotpanel.size();i++)
        {
            if(c_cardmap[c_robotpanel[i]].Type()==Card::shan && judge)
            {
                c_robotpanel[i]->setFront(true);
                c_robotpanel[i]->move((width() - c_size.width()) / 2-100,height() / 2 - 100);
                c_robotpanel.erase(c_robotpanel.begin()+i);
                updatePlayerCards(c_gct->getRobotPlayer());
                mess->MOUT("npc打出了闪");
                judge=0;
                break;
            }
        }
        if(judge)
        {
            qDebug()<<"没有打出闪"<<endl;
            robot_life--;
            c_robotlife->setLife(robot_life);
        }
    }

    else
    {
        qDebug()<<"响应npc阶段"<<endl;
        xiangying->showCountDown();
//        userPlayhand *subround = new userPlayhand(player);
//        subround->start();
    }

}

void gamepanel::tao()
{
    Player* player=c_gct->getCurrentPlayer();
    if(player == c_gct->getRobotPlayer())
        hpchange(player,1);
    else if (player == c_gct->getUserPlayer())
        hpchange(player,1);
}

void gamepanel::wuzhong()
{
    onDispatchcard(c_gct->getCurrentPlayer());
}

void gamepanel::guohe()
{
    if(c_gct->getobjPlayer() == c_gct->getRobotPlayer())
    {
        (*c_robotpanel.begin())->setFront(true);
        (*c_robotpanel.begin())->move((width() - c_size.width()) / 2-100,height() / 2 - 100);
        c_robotpanel.erase(c_robotpanel.begin());
        c_robothand.remove(c_cardmap[*c_robotpanel.begin()]);
    }

    else if(c_gct->getobjPlayer() == c_gct->getUserPlayer())
    {
        (*c_userpanel.begin())->move((width() - c_size.width()) / 2+100,height() / 2 - 100);
        c_userpanel.erase(c_userpanel.begin());
        c_userhand.remove(c_cardmap[*c_userpanel.begin()]);
    }
    updatePlayerCards(c_gct->getobjPlayer());
}

void gamepanel::shunshou()
{
    if(c_gct->getobjPlayer() == c_gct->getRobotPlayer())
    {
        CardPanel *panel = new CardPanel(this);
        (*c_robotpanel.begin())->setFront(true);
        panel = (*c_robotpanel.begin());
        c_robotpanel.erase(c_robotpanel.begin());
        c_robothand.remove(c_cardmap[*c_robotpanel.begin()]);

        c_userpanel.append(panel);
        c_userhand.add(c_cardmap[panel]);
    }
    else if (c_gct->getobjPlayer() == c_gct->getUserPlayer())
    {
        CardPanel *panel = new CardPanel(this);
        (*c_userpanel.begin())->setFront(true);
        panel = (*c_userpanel.begin());
        panel->setFront(false);
        c_userpanel.erase(c_userpanel.begin());
        c_userhand.remove(c_cardmap[*c_userpanel.begin()]);

        c_robotpanel.append(panel);
        c_robothand.add(c_cardmap[panel]);

    }
    updatePlayerCards(c_gct->getRobotPlayer());
    updatePlayerCards(c_gct->getUserPlayer());
}

void gamepanel::nanman()
{
    Player* player = c_gct->getobjPlayer();
    if(player == c_gct ->getUserPlayer())
    {
        nan_jud=1;
        qDebug()<<"响应npc南蛮入侵阶段"<<endl;
        xiangying->showCountDown();
        userPlayhand *subround = new userPlayhand(player);
        subround->start();
    }

    else if (c_gct->getRobotPlayer() == player)
    {
        hpchange(c_gct->getobjPlayer(),-1);
        for(int i=0;i<c_robotpanel.size();i++)
        {
            if(c_cardmap[c_robotpanel[i]].Type()==Card::sha )
            {
                npcPlayCard(i);
                mess->MOUT("NPC打出了杀");
                hpchange(c_gct->getobjPlayer(),1);
                break;
            }
        }
    }
}

void gamepanel::wangjian()
{
    Player* player = c_gct->getobjPlayer();
    if(player == c_gct ->getUserPlayer())
    {
        jud=1;
        qDebug()<<"响应npc万箭齐发阶段"<<endl;
        xiangying->showCountDown();
        userPlayhand *subround = new userPlayhand(player);
        subround->start();
    }

    else if (c_gct->getRobotPlayer() == player)
    {
        hpchange(c_gct->getobjPlayer(),-1);
        for(int i=0;i<c_robotpanel.size();i++)
        {
            if(c_cardmap[c_robotpanel[i]].Type()==Card::shan )
            {
                npcPlayCard(i);
                mess->MOUT("NPC打出了闪");
                hpchange(c_gct->getobjPlayer(),1);
                break;
            }
        }
    }
}

void gamepanel::hpchange(Player* player,int num)
{
    qDebug()<<"血量发生变化"<<endl;
//    player = c_gct->getobjPlayer();
    if(player == c_gct->getRobotPlayer())
    {
        robot_life+=num;
        c_robotlife->setLife(robot_life);
    }

    else if(player == c_gct->getUserPlayer())
    {
       user_life+=num;
        c_userlife->setLife(user_life);
    }
}

void gamepanel::lifeChange()
{
    qDebug()<<"响应结束"<<endl;
    if(jud)
    {
        user_life--;
        qDebug()<<user_life<<endl;
        c_userlife->setLife(user_life);
        jud=1;
    }
    if(nan_jud)
    {
        user_life--;
        c_userlife->setLife(user_life);
        nan_jud=1;
    }
}

void gamepanel::judchange()
{
    jud=0;
    nan_jud=0;
}

void gamepanel::gameWin()
{

    if(robot_life == 0)
    {
        endScene* es = new endScene(this);
        es->move(rect().width()/2-es->width()/2,rect().height()/2-es->height()/2);
        es->setWinner(1);
        mess->MOUT("玩家胜利");
    }
    else if (user_life == 0)
    {
        endScene* es = new endScene(this);
        es->move(rect().width()/2-es->width()/2,rect().height()/2-es->height()/2);
        es->setWinner(0);
        mess->MOUT("npc胜利");
    }
}

CardPanel *gamepanel::getCurrtCard()
{
    return currt_card;
}

void gamepanel::paintEvent(QPaintEvent *ev)
{
    Q_UNUSED(ev);
    QPainter p(this);
    p.drawPixmap(rect(),c_background);


//    QPixmap pix(":/img/bac.png");
//    QPixmap pix1(":/img/prescene.png");
//    QPixmap pix2(":/img/start.png");
//    const QRect cardsRect[] =
//    {
//        QRect(90, 130, 100, height() - 200),
//        QRect(rect().right() - 190, 130, 100, height() - 200),
//        QRect(250, rect().bottom() - 120, width() - 500, 100)
//    };

//    const QRect playHandRect[] =
//    {
//        QRect(260, 150, 100, 100),
//        QRect(rect().right() - 360, 150, 100, 100),
//        QRect(150, rect().bottom() - 290, width() - 300, 105)
//    };

//    for(int i=0;i<3;i++)
//    {
//        p.drawPixmap(cardsRect[i],pix);
//        p.drawPixmap(playHandRect[i],pix1);
//    }
    c_basecardPos = QPoint((width() - c_size.width()) / 2,
                           height() / 2 - 100);

//    QRect cardRect = c_contextmap[c_playerlist.at(0)].cardRect;
//    int  unit=cardRect.top() - c_basecardPos.y() / 100;
//    p.drawEllipse(c_basecardPos,50,50);

}

