#ifndef CITY_H
#define CITY_H
#include "interfaces/icity.hh"
#include "interfaces/ipassenger.hh"
#include "interfaces/ivehicle.hh"
#include "interfaces/istop.hh"
#include "actors/stop.hh"
#include "actors/passenger.hh"
#include <QString>
#include <QTime>
#include <memory>
#include <list>
#include <QDebug>
#include <QPainter>
#include <typeinfo>
//#include <QtGlobal>
//#include <QtTest>
namespace StudentSide
{
using namespace CourseSide;

const QString DEFAULT_CITY_MAP_SMALL_FILE = ":/offlinedata/offlinedata/kartta_pieni_500x500.png";
const QString DEFAULT_CITY_MAP_LARGE_FILE = ":/offlinedata/offlinedata/kartta_iso_1095x592.png";

class City : public Interface::ICity
{
public:
    City();
    ~City();

    void setBackground(QImage& basicbackground, QImage& bigBackground);
    void setClock(QTime clock);
    void addStop(std::shared_ptr<Interface::IStop> stop);

    // This function is called after setBackground() and setClock()
    void startGame();

    // return true if the game is over
    bool isGameOver() const;

    void addActor(std::shared_ptr<Interface::IActor> newactor);
    void removeActor(std::shared_ptr<Interface::IActor> actor);
    void actorRemoved(std::shared_ptr<Interface::IActor> actor);
    bool findActor(std::shared_ptr<Interface::IActor> actor) const;
    void actorMoved(std::shared_ptr<Interface::IActor> actor);
    std::vector<std::shared_ptr<Interface::IActor>> getNearbyActors(Interface::Location loc) const;
    std::shared_ptr<QImage> getBackground(const QString &size) const;

private:
    QImage basicBackground_;
    QImage bigBackground_;
    QTime cityTimer_;
    std::list<std::shared_ptr<Interface::IStop>> stops_;
    std::list<std::shared_ptr<Interface::IVehicle>> buses_;
    std::list<std::shared_ptr<Interface::IPassenger>> passengers_;
    bool started = false;
};
}
#endif // CITY_H
