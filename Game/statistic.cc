#include "statistic.hh"

StudentSide::Statistic::Statistic(CourseSide::Nysse* bus, std::shared_ptr<Interface::ICity>  city)
{
    bus_ = bus;
    numPassenger_ = bus->getPassengers().size();
    score_ = 0;
    city_ = city;
}

void StudentSide::Statistic::morePassengers(int num)
{
    bus_->addPassenger(num);
}

void StudentSide::Statistic::nysseRemoved()
{
    bus_->remove();
}

void StudentSide::Statistic::newNysse()
{
    bus_->setCity(city_);
}

void StudentSide::Statistic::nysseLeft()
{
    bus_->remove();
}
