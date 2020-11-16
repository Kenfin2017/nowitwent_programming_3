#include <QApplication>
#include <QImage>
#include "graphics/simplemainwindow.hh"

using namespace CourseSide;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Q_INIT_RESOURCE(offlinedata);

    SimpleMainWindow window;

    // Load image according to size option
    QImage map(":/offlinedata/offlinedata/kartta_iso_1095x592.png","png");

    window.show();
    window.setPicture(map);

    return a.exec();
}
