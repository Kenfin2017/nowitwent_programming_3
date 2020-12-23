#include "digitalclock.hh"

namespace StudentSide {


DigitalClock::DigitalClock(QWidget *parent, QTimer* timer): QLCDNumber(parent)
{
    setSegmentStyle(Filled);
    timer_ = timer;
    setDigitCount(11); // "HH:MM:SS AP"
    resize(350, 60);
}

void DigitalClock::showTime(QTime* time)
{
    QString text = time->toString("hh:mm:ss a");
    display(text);
}

}
