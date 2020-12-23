#ifndef GAMELOGIC_HH
#define GAMELOGIC_HH
#include "offlinereader.hh"
#include "actors/nysse.hh"
#include "interfaces/icity.hh"
#include "city.hh"

#include <list>
#include <QTime>
#include <QTimer>
#include <QDebug>
namespace StudentSide{

using namespace CourseSide;
// default files
const QString DEFAULT_STOPS_FILE = ":/offlinedata/offlinedata/full_stations_kkj3.json";
const QString DEFAULT_BUSES_FILE = ":/offlinedata/offlinedata/final_bus_liteN.json";

class GameLogic : public QObject
{
    Q_OBJECT
public:

    /**
     * @brief Default constructor
     * @param parent is a QObject pointer that defaults to 0
     */
    GameLogic(QObject* parent = 0, std::shared_ptr<City> city = 0, QTimer* timer_ = 0);

    /**
     * @brief readOfflineData uses OfflineReader class to read given offlinedata-files
     * @param buses filepath for busfile
     * @param stops filepath for stopfile
     * @pre -
     * @return returns true if data files are read correctly, else false
     */
    void readOfflineData(const QString& buses, const QString& stops);

    /**
     * @brief startGame
     * @pre GameLogic constructor is called
     * @post game should have generate a list of buses and connect with related signals
     */
    void startGame();

    /**
     * @brief getBus
     * @pre gameLogic has run startGame()
     * @return vector buses_
     */
    std::vector<std::shared_ptr<Nysse>> getBus() const;

    /**
     * @brief getPassenger
     * @pre gameLogic has run startGame()
     * @return vector passengers_
     */
    std::vector<std::shared_ptr<Passenger>> getPassenger() const;

    /**
     * @brief getCity
     * @pre gameLogic has run setCity()
     * @return pointer to city_
     */
    std::shared_ptr<City> getCity() const;

    /**
     * @brief getOfflineData
     * @return this offlineData
     */
    std::shared_ptr<OfflineData> getOfflineData() const;

    /**
     * @brief setCity
     * @pre city parameter is initialized
     * @post city_ is set
     */
    void setCity(std::shared_ptr<City> city);

    /**
     * @brief getClock
     * @pre clock is set
     * @return clock ingame time
     */
    QTime *getClock() const;

    // ratio between game time and real time
    static const int TIME_SPEED;
    // time between updates in milliseconds
    static const int UPDATE_INTERVAL_MS;

public slots:
    /**
     * @brief advance handles the movement and removal of buses and passengers.
     * Gets called every timeout by increaseTime
     * @pre GameLogic::start() has been called
     */
    void advance();

    /**
     * @brief increaseTime gets called when timer_ timeouts and increases time when
     * game is not over, calls advance to move buses to next position.
     */
    void increaseTime();

signals:
    /**
     * @brief gameAdvanced (signal) tells mainWindow to update its items position and state
     */
    void gameAdvanced();

private:
    // game state gameStarted=false by default
    bool gameStarted;

    // Record current time
    QTime* time_;

    // Timer that increments time_ every second
    QTimer* timer_;

    // Adds buses to the traffic depending on the time_, called by constructor
    void addBuses();

    // List of buses generate from readOffline data
    std::vector<std::shared_ptr<Nysse>> buses_;

    // List of passengers
    std::vector<std::shared_ptr<Passenger>> passengers_;

    // Offline data reader
    std::shared_ptr<OfflineData> offlineData_;

    // City
    std::shared_ptr<City> city_;

    void addStopsAndPassengers();

    // Returns true if new location was succesfully calculated
    // False if bus arrived to the final stop or it shouldn't be in traffic
    bool calculateNewLocationForBus(std::shared_ptr<Nysse> bus);
};

}
#endif // GAMELOGIC_HH
