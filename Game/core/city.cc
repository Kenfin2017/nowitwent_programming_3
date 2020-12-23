#include "city.hh"

namespace StudentSide
{

City::City()
{
    basicBackground_.load(DEFAULT_CITY_MAP_SMALL_FILE, "png");
    bigBackground_.load(DEFAULT_CITY_MAP_LARGE_FILE, "png");
    cityTimer_.setHMS(QTime::currentTime().hour(),QTime::currentTime().minute(),QTime::currentTime().second());
}

City::~City(){
    qDebug() << "City removed!";
}

void City::setBackground(QImage& basicBackground, QImage& bigBackground){
    if(!basicBackground.isNull() && !bigBackground.isNull()){
        QPainter painter;
        QPointF pos(0,0);
        // start painting
        painter.begin(&basicBackground_);
        painter.drawImage(pos, basicBackground);
        painter.end();

        painter.begin(&bigBackground_);
        painter.drawImage(pos, bigBackground);
        painter.end();
    }
}

void City::setClock(QTime clock){
    if(clock.isValid()){
        cityTimer_.setHMS(clock.hour(), clock.minute(), clock.second());
    }
    else{
        qDebug() << "Clock is not valid";
    }
}

void City::addStop(std::shared_ptr<Interface::IStop> stop)
{
    if(stop->getName() == ""){
        qDebug() << "Stop does not have name!";
        return;
    }
    else{
        stops_.push_back(stop);
        qDebug() << "New stop added";
    }
}

void City::startGame(){
    started = true;
    qDebug("City started!");
}

bool City::isGameOver() const{
    if(!started){
        qDebug("City ended!");
    }
    return !started;
}


void City::addActor(std::shared_ptr<Interface::IActor> newactor){
    if(newactor->isRemoved()){
        qDebug()<< "Actor is already removed";
    }
    else{
        if(typeid(newactor).before(typeid(std::shared_ptr<Interface::IVehicle>))){
            buses_.push_back(newactor);
            qDebug() << "Bus Added";
        }
        if(typeid(newactor).before(typeid(std::shared_ptr<Interface::IPassenger>))){
            passengers_.push_back(newactor);
            qDebug() << "Passenger Added";
        }
    }
}

void City::removeActor(std::shared_ptr<Interface::IActor> actor){
    if(typeid(actor).before(typeid(std::shared_ptr<Interface::IVehicle>))){
        for(auto b = buses_.begin(); b != buses_.end(); b++ ){
            if(actor.get() == b->get()){
                buses_.remove(*b);
                break;
            }
        }
    }
    else if(typeid(actor).before(typeid(std::shared_ptr<Interface::IPassenger>))){
        for(auto p = passengers_.begin(); p != passengers_.end(); p++ ){
            if(actor.get() == p->get()){
                passengers_.remove(*p);
                break;
            }
        }
    }
}

void City::actorRemoved(std::shared_ptr<Interface::IActor> actor)
{
    if (actor->isRemoved()){
        qDebug("Actor is removed from the game");
    }
    else{
        qDebug("Actor is active");
    }
}

bool City::findActor(std::shared_ptr<Interface::IActor> actor) const
{
    if(typeid(actor).before(typeid(std::shared_ptr<Interface::IVehicle>))){
        for(auto b = buses_.begin(); b != buses_.end(); b++ ){
            if(b->get() == actor.get()){
                return true;
            }
        }
    }
    else if(typeid(actor).before(typeid(std::shared_ptr<Interface::IPassenger>))){
        for(auto p = passengers_.begin(); p != passengers_.end(); p++ ){
            if(p->get() == actor.get()){
                return true;
            }
        }
    }
    return false;
}

void City::actorMoved(std::shared_ptr<Interface::IActor> actor)
{
    if(started){
//        if(typeid(actor).before(typeid(std::shared_ptr<Interface::IVehicle>))){
//            for(auto bus = buses_.begin(); bus != buses_.end(); bus++){
//                if(bus == actor){
//                    qDebug() << "bus has moved!";
//                }
//            }
//        }
//        else if(typeid(actor).before(typeid(std::shared_ptr<Interface::IPassenger>))){
//            for(auto pas = passengers_.begin(); pas != passengers_.end(); pas++){
//                if(actor->giveLocation().giveX() != pas->get()->giveLocation().giveX()){
//                    qDebug() << "passenger has moved";
//                }
//            }
//        }
        if(actor->isRemoved()){
            qDebug() << "Actor removed, and should not be moving";
        }
    }
}

std::vector<std::shared_ptr<Interface::IActor> > City::getNearbyActors(Interface::Location loc) const
{
    std::vector<std::shared_ptr<Interface::IActor>> closebyActors;

    for(std::shared_ptr<Interface::IActor> bus: buses_){
       if(bus.get()->giveLocation().isClose(loc)){
           closebyActors.push_back(bus);
       }
    }
    for(std::shared_ptr<Interface::IActor> pas: passengers_){
       if(pas.get()->giveLocation().isClose(loc)){
           closebyActors.push_back(pas);
       }
    }

    return closebyActors;
}

std::shared_ptr<QImage> City::getBackground(const QString &size) const
{
    if(size == "small"){
        return std::make_shared<QImage>(basicBackground_);
    }
    else if(size == "large"){
        return std::make_shared<QImage>(bigBackground_);
    }
    else{
        return std::make_shared<QImage>(bigBackground_);
    }
}

std::shared_ptr<Interface::IActor> City::getBus()
{
    srand(time(NULL));
    int randIdx = rand() % buses_.size();
    int index = 0;
    for(std::shared_ptr<Interface::IActor> bus: buses_){
        if(index++ == randIdx){
            return bus;
        }
    }
    return buses_.front();
}

unsigned int City::busCount()
{
    return buses_.size();
}
}
