#include "statistic.hh"

using namespace StudentSide;
Statistic::Statistic()
{
    bus_ = nullptr;
    player_ = nullptr;
    score_ = 0;
}

Statistic::~Statistic()
{
}

void Statistic::morePassengers(int num)
{
    if(num < 0){
        qWarning() << "Statistic: number passengers to add is supposed to be positive";
    }
    else{
        for(unsigned int i =0; i < (unsigned int)num && i < passengers_.size(); i++){
            std::shared_ptr<Interface::IPassenger> pas = std::dynamic_pointer_cast<Interface::IPassenger>(passengers_.at(i));
            bus_->addPassenger(pas);
            if(!pas->isInVehicle()){
                qWarning() << "Statistic: Failed to add passenger to bus";
            }
        }
        qInfo("Statistic: Added %d passengers to bus", num);
    }
}

void Statistic::nysseRemoved()
{
}

void Statistic::newNysse()
{
    if(bus_ != nullptr){
        qInfo() << "Statistic: New bus added.";
    }else{
        qWarning() << "Statistic: Bus is null.";
    }
}

void Statistic::nysseLeft()
{
    bus_->remove();
    if(!bus_->isRemoved()){
        qWarning() << "Statistic: Failed to remove bus.";
    }
    else{
        qInfo() << "Statistic: Bus is removed.";
    }
}

int Statistic::givePoints() const
{
    return score_;
}

void Statistic::passengerDied(int num)
{
    if(passengers_.size() > 0){
        for(int i = 0; i < num; i++){
            passengers_.at(i)->remove();
            if(!passengers_.at(i)->isInVehicle()){
                qWarning() << "Statistic: Removed passenger is still in vehicle.";
            }
            else{
                qInfo() << "Statistic: Removed passenger removed from vehicle.";
            }
        }
    }
}

void Statistic::setBus(std::shared_ptr<Nysse> newBus)
{
    if(newBus != nullptr){
        bus_ = newBus;
        qInfo("Statistic: Bus nro %d assigned for statistic.",newBus->getLine());
    }
    else{
        qWarning() << "Statistic: Attempt to add null bus to statistic.";
    }
}


std::shared_ptr<Nysse> Statistic::getBus() const
{
    return bus_;
}

void Statistic::addPassenger(std::shared_ptr<Passenger> passenger)
{
    if(passenger != nullptr){
        passengers_.push_back(passenger);
        qInfo() << "Statistic: Added new passenger for statistic." ;
    }
    else{
        qWarning() << "Statistic: Attempt to add null passenger to statistic.";
    }
}

std::vector<std::shared_ptr<Passenger>> Statistic::getPassengers() const
{
    return passengers_;
}

std::shared_ptr<PlayerActorItem> Statistic::getPlayer() const
{
    return player_;
}

void Statistic::setPlayer(std::shared_ptr<PlayerActorItem> player)
{
    if(player != nullptr){
        player_ = player;
        qInfo() << "Statistic: Added new passenger for statistic." ;
    }
    else{
        qWarning() << "Statistic: Attempt to add null player item.";
    }
}
