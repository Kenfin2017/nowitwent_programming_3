#include "gamelogic.hh"
namespace StudentSide {

StudentSide::GameLogic::GameLogic(QObject* parent):
    QObject(parent),
    gameStarted(false),
    time_(QTime(QTime::currentTime().hour(), QTime::currentTime().minute(), QTime::currentTime().second()))
{

}

void GameLogic::readOfflineData(const QString &buses, const QString &stops)
{
    OfflineReader offlinereader;
    if((offlineData_ = offlinereader.readFiles(buses, stops)) == NULL) {
        qDebug() << "Error reading offline data";
    }
    else{
        qDebug() << "Data reader success";
    }
}

void GameLogic::startGame()
{
    readOfflineData(DEFAULT_BUSES_FILE,DEFAULT_STOPS_FILE);
    if(offlineData_ != NULL){
        for(std::shared_ptr<BusData> bus : offlineData_->buses){
            for (QTime starttime : bus->schedule) {
                std::shared_ptr<Nysse> newBus = std::make_shared<Nysse>(bus->routeNumber);
                newBus->setRoute(bus->timeRoute2, starttime);
                newBus->calcStartingPos(time_);
                buses_.push_back(newBus);
            }
        }
    }
}

std::shared_ptr<Nysse> GameLogic::getBus() const
{
    srand(time(NULL));
    unsigned int idx = rand() % buses_.size();
    return buses_.at(idx);
}

std::shared_ptr<OfflineData> GameLogic::getOfflineData() const
{
    return offlineData_;
}

}
