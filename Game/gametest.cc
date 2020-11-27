#include "gametest.hh"

Gametest::Gametest()
{

}

void Gametest::testMorePassengers()
{
    QFETCH(unsigned int, num);

    // Performing the test

    QVERIFY2(num>0);

    try {
        QVERIFY2(num>0);
    }  catch () {
        qDebug("The number of new passangers added can be less than 0");
    }


}

void Gametest::testNysseRemoved()
{

    try {
        bus_->remove();
    }  catch () {
        qDebug("The bus is not removed");
    }



}


void Gametest::testNewNysse()
{

    try {
        bus_->setCity(city_);
    }  catch () {
        qDebug("The new nysse is not added to the game");
    }



}



void Gametest::testNysseLeft()
{

    try {
        bus_->remove();
    }  catch () {
        qDebug("The nysse has not left the game");
    }



}



QTEST_APPLESS_MAIN(gametest)
