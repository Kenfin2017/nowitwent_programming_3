#include <QApplication>
#include <QImage>
#include "graphics/gamemainwindow.hh"
#include "creategame.hh"

using namespace StudentSide;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Q_INIT_RESOURCE(offlinedata);

    CreateGame game;

    return a.exec();
}
