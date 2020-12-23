#ifndef DIGITALCLOCK_HH
#define DIGITALCLOCK_HH

#include <QLCDNumber>
#include <QTimer>
#include <QTime>
namespace StudentSide {
class DigitalClock : public QLCDNumber
{
    Q_OBJECT
public:
    /**
     * @brief DigitalClock constructor
     * @param parent
     * @param timer
     */
    DigitalClock(QWidget* parent = 0, QTimer* timer = 0);

    /**
     * @brief showTime
     * @param time
     * @post updates time value to display
     */
    void showTime(QTime* time);
private:
    QTimer* timer_;
};

}
#endif // DIGITALCLOCK_HH
