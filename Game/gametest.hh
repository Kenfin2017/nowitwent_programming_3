#ifndef GAMETEST_HH
#define GAMETEST_HH

#include <QtTest>
#include "gametest.hh"

class Gametest : public QObject
{
     Q_OBJECT

public:
    Gametest();

private Q_SLOTS:

    void Gametest::testMorePassengers();
    void Gametest::testNysseRemoved();
    void Gametest::testNewNysse();
    void Gametest::testNysseLeft()


};

#endif // GAMETEST_HH


