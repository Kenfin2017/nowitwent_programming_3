#include <QApplication>
#include <QImage>
#include "gamemainwindow.hh"
#include "creategame.hh"

using namespace StudentSide;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Q_INIT_RESOURCE(offlinedata);

    CreateGame game;
//    GameMainWindow gamewindow;
//    gamewindow.show();
    return a.exec();
}
