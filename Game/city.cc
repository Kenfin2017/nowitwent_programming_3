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
    qDebug("City ended!");
    return true;
}


void City::addActor(std::shared_ptr<Interface::IActor> newactor){
    if(findActor(newactor)){
        qDebug()<< "Actor already exists in city";
    }
    else{
        qDebug() << typeid(newactor).name();
        if(typeid(newactor).name() == typeid(std::shared_ptr<CourseSide::Nysse>).name()){
            std::shared_ptr<Interface::IVehicle> newbus = std::dynamic_pointer_cast<Interface::IVehicle>(newactor);
            buses_.push_back(newbus);
        }
        if(typeid(newactor).name() == typeid(std::shared_ptr<CourseSide::Passenger>).name()){
            std::shared_ptr<Interface::IPassenger> newPassenger = std::dynamic_pointer_cast<Interface::IPassenger>(newactor);
            passengers_.push_back(newPassenger);
        }
    }
}

void City::removeActor(std::shared_ptr<Interface::IActor> actor){
    qDebug() <<"Remove Actor type: "<< typeid(actor.get()).name();
    if(typeid(actor).name() == typeid(std::shared_ptr<CourseSide::Nysse>).name()){
        std::shared_ptr<Interface::IVehicle> bus = std::dynamic_pointer_cast<Interface::IVehicle>(actor);
        for(auto b = buses_.begin(); b != buses_.end(); b++ ){
            if(bus.get() == b->get()){
                buses_.remove(*b);
                break;
            }
        }
    }
    else if(typeid(actor).name() == typeid(std::shared_ptr<CourseSide::Passenger>).name()){
        std::shared_ptr<Interface::IPassenger> passenger = std::dynamic_pointer_cast<Interface::IPassenger>(actor);
        for(auto p = passengers_.begin(); p != passengers_.end(); p++ ){
            if(passenger.get() == p->get()){
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
    if(typeid(actor).name() == typeid(std::shared_ptr<CourseSide::Nysse>).name()){
        std::shared_ptr<Interface::IVehicle> bus = std::dynamic_pointer_cast<Interface::IVehicle>(actor);
        for(auto b = buses_.begin(); b != buses_.end(); b++ ){
            if(b->get() == bus.get()){
                return true;
            }
        }
    }
    else if(typeid(actor.get()).name() == typeid(std::shared_ptr<CourseSide::Passenger>).name()){
        std::shared_ptr<Interface::IPassenger> passenger = std::dynamic_pointer_cast<Interface::IPassenger>(actor);
        for(auto p = passengers_.begin(); p != passengers_.end(); p++ ){
            if(passenger.get() == p->get()){
                return true;
            }
        }
    }
    return false;
}

void City::actorMoved(std::shared_ptr<Interface::IActor> actor)
{
    if(started){
        if(typeid(actor).name() == typeid(std::shared_ptr<CourseSide::Nysse>).name()){
            for(auto bus = buses_.begin(); bus != buses_.end(); bus++){
                // compare referenced actor has different location
                if(actor->giveLocation().giveX() != bus->get()->giveLocation().giveX()){
                    qDebug() << "bus has moved!";
                }
            }
        }
        else if(typeid(actor).name() == typeid(std::shared_ptr<CourseSide::Passenger>).name()){
            for(auto pas = passengers_.begin(); pas != passengers_.end(); pas++){
                if(actor->giveLocation().giveX() != pas->get()->giveLocation().giveX()){
                    qDebug() << "passenger has moved";
                }
            }
        }
    }
}

std::vector<std::shared_ptr<Interface::IActor> > City::getNearbyActors(Interface::Location loc) const
{
    std::vector<std::shared_ptr<Interface::IActor>> closebyActors;
    for(std::shared_ptr<Interface::IVehicle> bus: buses_){
       if(bus.get()->giveLocation().isClose(loc)){
           closebyActors.push_back(std::dynamic_pointer_cast<Interface::IActor>(bus));
       }
    }
    for(std::shared_ptr<Interface::IPassenger> pas: passengers_){
       if(pas.get()->giveLocation().isClose(loc)){
           closebyActors.push_back(std::dynamic_pointer_cast<Interface::IActor>(pas));
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
}
