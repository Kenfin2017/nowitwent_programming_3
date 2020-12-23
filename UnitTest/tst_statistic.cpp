#include <QtTest>
// add necessary includes here
#include "tst_statistic.hh"
using namespace StudentSide;

StatisticTest::StatisticTest()
{
    std::shared_ptr<Nysse> bus = std::make_shared<Nysse>(25);
    stat = new Statistic();
    stat->setBus(bus);
}

StatisticTest::~StatisticTest()
{

}

void StatisticTest::initTestCase()
{
    qInfo() << "Called before everything else.";
}

void StatisticTest::testNewNysse()
{
    stat->newNysse();
    QVERIFY2(stat->getBus() != nullptr, "Adding new bus as null pointer.");
}

void StatisticTest::testMorePassenger()
{
    QVERIFY2(stat->getBus() != nullptr, "bus was not created");

    unsigned int passCntBeforeAdd = stat->getBus()->getPassengers().size();
    stat->morePassengers(3);
    unsigned int passCntAfterAdd = stat->getBus()->getPassengers().size();

    QVERIFY2(passCntAfterAdd > passCntBeforeAdd, "morePassergers(): passengers count error");
}

void StatisticTest::testGivePoints()
{
    qInfo("Points count : %d", stat->givePoints());
    QVERIFY2(true, "Should not print this message");
}

void StatisticTest::testPassengerDied()
{
    int passCntBefore = stat->getPassengers().size();
    stat->passengerDied(1);
    int passCntAfter = stat->getPassengers().size();

    QVERIFY2(passCntAfter < passCntBefore, "passengerDied(): passenger count was not different");
}

void StatisticTest::testNysseLeft()
{
    stat->nysseLeft();
    QVERIFY2(stat->getBus()->isRemoved(), "bus was not removed");
}

QTEST_APPLESS_MAIN(StatisticTest)
//#include "tst_statistic.moc"
