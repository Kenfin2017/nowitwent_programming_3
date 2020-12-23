#include "gamelogic.hh"
namespace StudentSide {

GameLogic::GameLogic(QObject* parent, std::shared_ptr<City> city, QTimer* timer):
    QObject(parent),
    gameStarted(false),
    timer_(timer),
    city_(city)
{
    time_ = new QTime(5,25,0);
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
    // add buses
    readOfflineData(DEFAULT_BUSES_FILE,DEFAULT_STOPS_FILE);
    if(offlineData_ != NULL){

        for(std::shared_ptr<BusData> bus: offlineData_->buses){
        // for this game, we've just focused on few routes 25, 27 and 11
//            if(bus->routeNumber == 25 || bus->routeNumber == 27 || bus->routeNumber == 11){
                std::shared_ptr<Nysse> newBus = std::make_shared<Nysse>(bus->routeNumber);
                newBus->setRoute(bus->timeRoute2, bus->schedule.front());
                newBus->setCity(city_);
                newBus->calcStartingPos(*time_);
                buses_.push_back(newBus);
                city_->addActor(newBus);
//            }
        }
    }

    addStopsAndPassengers();
    // set timer and timeout signal connection
    city_->setClock(*time_);
    city_->startGame();
}

std::vector<std::shared_ptr<Nysse>> GameLogic::getBus() const
{
    return buses_;
}

std::vector<std::shared_ptr<Passenger> > GameLogic::getPassenger() const
{
    return passengers_;
}

std::shared_ptr<City> GameLogic::getCity() const
{
    return city_;
}

std::shared_ptr<OfflineData> GameLogic::getOfflineData() const
{
    return offlineData_;
}

void GameLogic::setCity(std::shared_ptr<City> city)
{
    city_ = city;
}

QTime *GameLogic::getClock() const
{
    return time_;
}

void GameLogic::advance()
{
    emit gameAdvanced();

    for (std::vector<std::shared_ptr<Passenger>>::iterator it = passengers_.begin();
         it != passengers_.end(); it++) {

        // Check if removed
        if (it->get()->isRemoved()) {
            // Remove passenger from buses or stops accounting
            if (it->get()->isInVehicle()) {
                it->get()->getVehicle()->removePassenger(*it);
            } else {
                std::shared_ptr<Stop> pysakki = std::dynamic_pointer_cast<Stop>(it->get()->getStop());
                pysakki->removePassenger(*it);
            }

            // Remove passenger from accounting
            if (city_->findActor(*it)) {
                city_->removeActor(*it);
            }
            it = passengers_.erase(it);
            continue;
        }
    }
    // Goes through current buses and removes ones that are removed
    for (std::vector<std::shared_ptr<Nysse>>::iterator it = buses_.begin(); it != buses_.end(); it++ ) {
        std::shared_ptr<Nysse> bus = *it;

        // Check if removed
        if (bus->isRemoved()) {

            // If bus is marked removed, go through its passengers and check that they are marked as removed too
            // If not marked --> mark as removed and remove the bus and its passengers from data structures
            for (std::shared_ptr<Interface::IPassenger> passengerif : bus->getPassengers()) {
                std::shared_ptr<Passenger> passenger = std::dynamic_pointer_cast<Passenger> (passengerif);

                if (!passenger->isRemoved()) {
                    passenger->remove();
                }
                // if city keeps track of passengers in removed bus, remove passengers from city
                if (city_->findActor(passenger)) {
                    city_->removeActor(passenger);
                }
            }
            qDebug() << "Removing bus: " << QString::fromStdString(bus->getName());

            std::shared_ptr<Interface::IActor> busToRemove = std::dynamic_pointer_cast<Interface::IActor> (*it);

            if (city_->findActor(busToRemove)) {
                city_->removeActor(busToRemove);
            }
            it = buses_.erase(it);
            continue;
        }

        // move the bus
        bool ret = calculateNewLocationForBus(bus);

        if (!ret) { // Remove bus if at final stop or wrong time
            qDebug() << "Bus has run out of the city";
            // Put passengers to the final stop of the bus
            std::vector<std::shared_ptr<Interface::IPassenger>> passengers = bus->getPassengers();
            std::weak_ptr<Stop> finalStop = bus->getFinalStop();

            // every passenger moved out of bus before it is removed
            for (auto passengerIt = passengers.begin(); passengerIt != passengers.end(); passengerIt++) {
                // assuming that passengers are of certain type
                std::shared_ptr<Passenger> passenger = std::dynamic_pointer_cast<Passenger>(*passengerIt);
                Q_ASSERT(passenger != nullptr);

                // Updates passenger to the final stop
                // Location of the passenger is already updated at
                // previous point of time, when bus arrived at final stop
                passenger->enterStop(finalStop);
                bus->removePassenger(passenger);
                finalStop.lock()->addPassenger(passenger);
                city_->actorMoved(passenger);
            }
            // check from city if bus is already removed
            if (city_->findActor(*it)) {
                city_->removeActor(*it);
            }
        }
    }
    // go through all stops that have buses
    for (std::shared_ptr <Nysse> bus : buses_) {
        std::shared_ptr <Stop> stop = bus->getStop().lock();

        if (stop != nullptr) {
            // 1. move passengers to stop if they want to

            for (std::shared_ptr <Interface::IPassenger> ipassenger : bus->getPassengers()) {
                std::shared_ptr <Passenger> passenger = std::dynamic_pointer_cast<Passenger> (ipassenger);
                Q_ASSERT(passenger != nullptr);

                if (passenger->wantToEnterStop(stop)) {
                    passenger->enterStop(stop);
                    bus->removePassenger(ipassenger);
                    stop->addPassenger(passenger);
                    city_->actorMoved(passenger);
                }
            }
        }
    }
    // 2. let every passenger in this stop about the buses in this stop at this time
    for (std::shared_ptr <Nysse> stopbus : buses_) {
        std::shared_ptr <Stop> stop = stopbus->getStop().lock();

        // stopbus is bus that is currently at the same stop
        if (stop != nullptr) {
            for (std::shared_ptr <Interface::IPassenger> istoppassenger : stop->getPassengers()) {
                std::shared_ptr <Passenger> stoppassenger = std::dynamic_pointer_cast<Passenger> (istoppassenger);
                Q_ASSERT(stoppassenger != nullptr);

                if (stoppassenger->wantToEnterNysse(stopbus)) {
                    stoppassenger->enterNysse(stopbus);
                    stop->removePassenger(stoppassenger);
                    stopbus->addPassenger(stoppassenger);
                    city_->actorMoved(stoppassenger);
                }
            }
        }
    }
    qDebug() << "New time " << time_->hour() << ":"<<time_->minute() << ":"<< time_->second();
    emit gameAdvanced();
}

bool GameLogic::calculateNewLocationForBus(std::shared_ptr<Nysse> bus)
{
    // Check if bus is at traffic
    // Deals with removing the buses at final stop
    // --> if bus got to final stop during last advance-routine, is ingame
    // time larger than the time of the buses last route point
    // --> return false and bus is deleted
    if (*time_ < bus->getTimeRoute().begin()->first || *time_ > bus->getTimeRoute().rbegin()->first) {
        // Not in traffic
        return false;
    }
    //qDebug() << "New time " << time_.hour() << ":"<<time_.minute();
    // Get new location

    Interface::Location newLocation = bus->getTimeRoute().find(*time_)->second.first;

    bus->move(newLocation);

    // passengers are moved
    std::vector<std::shared_ptr<Interface::IPassenger>> passengers = bus->getPassengers();
    for (auto it = passengers.begin(); it != passengers.end(); it++) {
        it->get()->move(newLocation);
        city_->actorMoved(*it);
    }

    return true;
}

void GameLogic::increaseTime()
{
    if ( city_->isGameOver() )
    {
        timer_->stop();
        return;
    }

    // add time and move bus
    *time_ = time_->addMSecs(UPDATE_INTERVAL_MS*TIME_SPEED);
    // move all old buses
    advance();
}

void GameLogic::addStopsAndPassengers()
{
    // give city all stops before creating passengers
    for ( std::shared_ptr<Stop> stop: offlineData_->stops) {
        city_->addStop(stop);
    }
    for ( std::shared_ptr<Stop> stop: offlineData_->stops) {
        // add random number of new passengers
        int randi = rand() % 10 + 1;

        for (int i = 0; i < randi; i++) {
            std::weak_ptr<Interface::IStop> destinationStop = offlineData_->stops.at( rand() % offlineData_->stops.size() );
            std::shared_ptr<Passenger> newPassenger = nullptr;
            newPassenger = std::make_shared<Passenger>( destinationStop );

            // add passengers for this stop
            newPassenger->enterStop( stop );
            passengers_.push_back(newPassenger);
            stop->addPassenger(newPassenger);
            city_->addActor(newPassenger);
        }
    }
}

// ratio between real time and game time
const int GameLogic::TIME_SPEED = 15;
// time between updates in milliseconds
const int GameLogic::UPDATE_INTERVAL_MS = 1000;
}
