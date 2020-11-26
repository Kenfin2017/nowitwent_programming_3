#ifndef GAMELOGIC_HH
#define GAMELOGIC_HH
#include "offlinereader.hh"
#include "actors/nysse.hh"
#include "interfaces/icity.hh"

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
    GameLogic(QObject* parent = 0);

    /**
     * @brief readOfflineData uses OfflineReader class to read given offlinedata-files
     * @param buses filepath for busfile
     * @param stops filepath for stopfile
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
     * @return a random bus from the list
     */
    std::shared_ptr<Nysse> getBus() const;

    /**
     * @brief getOfflineData
     * @return this offlineData
     */
    std::shared_ptr<OfflineData> getOfflineData() const;

private:
    // game state gameStarted=false by default
    bool gameStarted;

    // Record current time
    QTime time_;

    // Timer that increments time_ every second
    QTimer timer_;

    // Adds buses to the traffic depending on the time_, called by constructor
    void addBuses();

    // List of buses generate from readOffline data
    std::vector<std::shared_ptr<Nysse>> buses_;

    // Offline data reader
    std::shared_ptr<OfflineData> offlineData_;

};

}
#endif // GAMELOGIC_HH
