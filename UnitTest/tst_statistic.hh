#ifndef STATISTICTEST_HH
#define STATISTICTEST_HH

#include "core/statistic.hh"
#include <QString>
#include <QtTest>

using namespace StudentSide;
class StatisticTest : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief StatisticTest constructor
     */
    StatisticTest();

    ~StatisticTest();

private Q_SLOTS:
    /**
     * @brief Initialize test cases
     */
    void initTestCase();

    /**
     * @brief test case for morePassenger(int num)
     */
    void testMorePassenger();

    /**
     * @brief test case for newNysse()
     */
    void testNewNysse();

    /**
     * @brief test case for givePoints()
     */
    void testGivePoints();

    /**
     * @brief test case for passengerDied(int num)
     */
    void testPassengerDied();

    /**
     * @brief test case for nysseLeft
     */
    void testNysseLeft();

private:
    Statistic* stat;
    int points_;
};

#endif // STATISTICTEST_HH
