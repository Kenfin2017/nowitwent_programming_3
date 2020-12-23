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

    // from City IF
    void setBackground(QImage& basicbackground, QImage& bigBackground);
    void setClock(QTime clock);
    // This function is called after setBackground() and setClock()
    void startGame();

    void addActor(std::shared_ptr<Interface::IActor> newactor);
    void removeActor(std::shared_ptr<Interface::IActor> actor);
    void actorRemoved(std::shared_ptr<Interface::IActor> actor);
    bool findActor(std::shared_ptr<Interface::IActor> actor) const;
    void actorMoved(std::shared_ptr<Interface::IActor> actor);
    std::vector<std::shared_ptr<Interface::IActor>> getNearbyActors(Interface::Location loc) const;
    void addStop(std::shared_ptr<Interface::IStop> stop);

    // return true if the game is over
    bool isGameOver() const;

    /**
     * @brief getBackground
     * @pre basicBackground and bigBackground are initialized
     * @param size: map size either "small" or "large"
     * @return pointer to Image with respect to size
     */
    std::shared_ptr<QImage> getBackground(const QString &size) const;

    /**
     * @brief getBus
     * @pre buses vector is initialized
     * @post return a pointer to a bus
     * @return a random bus from the buses vector
     * @exception strong
     */
    std::shared_ptr<Interface::IActor> getBus();

    /**
     * @brief busCount: return number of bus in city
     * @pre -
     * @return size of buses vector
     * @exception no throw
     */
    unsigned int busCount();

private:
    QImage basicBackground_;
    QImage bigBackground_;
    QTime cityTimer_;
    std::list<std::shared_ptr<Interface::IStop>> stops_;
    std::list<std::shared_ptr<Interface::IActor>> buses_;
    std::list<std::shared_ptr<Interface::IActor>> passengers_;
    bool started = false;
};
}
#endif // CITY_H
