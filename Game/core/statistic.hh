#ifndef STATISTIC_HH
#define STATISTIC_HH

#include "actors/nysse.hh"
#include "interfaces/istatistics.hh"
#include "interfaces/ipassenger.hh"
#include "core/city.hh"
#include "actors/passenger.hh"
#include "graphics/player_actoritem.hh"
#include "core/gamelogic.hh"
#include <QTime>
#include <QKeyEvent>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
using namespace CourseSide;
namespace StudentSide {

class Statistic : public Interface::IStatistics
{
public:

    Statistic();
    ~Statistic();

    // from IStatistic IF
    void morePassengers(int num);
    void nysseRemoved();
    void newNysse();
    void nysseLeft();
    int givePoints() const;
    void passengerDied(int num);

    /**
     * @brief setBus assign bus for statistic
     * @param newBus Nysse pointer
     */
    void setBus(std::shared_ptr<Nysse> newBus);

    /**
     * @brief getBus
     * @pre bus is created
     * @return pointer to bus
     */
    std::shared_ptr<Nysse> getBus() const;

    /**
     * @brief addPassenger add new passenger to vector
     * @param passenger Passenger pointer
     * @post passengers list add new passenger
     */
    void addPassenger(std::shared_ptr<Passenger> passenger);
    /**
     * @brief getPassengers
     * @pre passengers vector is created
     * @return vector of passengers pointers
     */
    std::vector<std::shared_ptr<Passenger>> getPassengers() const;

    /**
     * @brief getPlayer
     * @pre player is created
     * @return pointer to PlayerActorItem object
     */
    std::shared_ptr<PlayerActorItem> getPlayer() const;

    /**
     * @brief setPlayer assign playerItem in Statistic
     * @param player
     */
    void setPlayer(std::shared_ptr<PlayerActorItem> player);

private:
    unsigned int score_;
    unsigned int numPassenger_;

    std::shared_ptr<Nysse> bus_;
    std::vector<std::shared_ptr<Passenger>> passengers_;
    std::shared_ptr<PlayerActorItem> player_;
};

}

#endif // STATISTIC_HH
