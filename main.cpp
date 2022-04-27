#include "gamepanel.h"
#include"prescene.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PreScene w;
//    gamepanel w;
    w.show();
    return a.exec();
}
