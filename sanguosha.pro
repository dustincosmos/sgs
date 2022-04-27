QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    card.cpp \
    cardpanel.cpp \
    cards.cpp \
    countdown.cpp \
    endscene.cpp \
    gamecontrol.cpp \
    main.cpp \
    gamepanel.cpp \
    messagewidget.cpp \
    player.cpp \
    playerlife.cpp \
    prescene.cpp \
    robot.cpp \
    robotplayhand.cpp \
    userplayer.cpp \
    userplayhand.cpp

HEADERS += \
    card.h \
    cardpanel.h \
    cards.h \
    countdown.h \
    endscene.h \
    gamecontrol.h \
    gamepanel.h \
    messagewidget.h \
    player.h \
    playerlife.h \
    prescene.h \
    robot.h \
    robotplayhand.h \
    userplayer.h \
    userplayhand.h

FORMS += \
    gamepanel.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


RESOURCES += \
    res.qrc
