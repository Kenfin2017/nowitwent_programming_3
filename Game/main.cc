#include <QApplication>
#include <QImage>
#include "graphics/simplemainwindow.hh"

using namespace CourseSide;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Q_INIT_RESOURCE(offlinedata);

    SimpleMainWindow window;

    window.show();

    return a.exec();
}
