#ifndef STATISTIC_HH
#define STATISTIC_HH

#include "actors/nysse.hh"
#include "interfaces/istatistics.hh"
#include "city.hh"

namespace StudentSide{

using namespace CourseSide;
class Statistic : public Interface::IStatistics
{
public:

    Statistic(Nysse* bus, std::shared_ptr<Interface::ICity> city);
    ~Statistic();

    void morePassengers(int num);
    void nysseRemoved();
    void newNysse();
    void nysseLeft();

private:
    unsigned int score_;
    unsigned int numPassenger_;
    Nysse* bus_;
    std::shared_ptr<Interface::ICity> city_;
};

}

#endif // STATISTIC_HH
