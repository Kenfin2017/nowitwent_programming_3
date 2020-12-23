#include "bus_actoritem.hh"

namespace StudentSide{
BusActorItem::BusActorItem(QGraphicsItem* parent, QTimer* timer): QObject(), QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(BUS_ICON_FILE).scaled(20,20, Qt::KeepAspectRatio));
    timer_ = timer;

    pLabel = new QLabel(QString::fromStdString(std::to_string(numPassenger)));
    pProxyWidget = new QGraphicsProxyWidget(this); // set proxy parent to busActorItem
    pProxyWidget->setWidget(pLabel); // add QWidget based object to the proxy
    pLabel->move(5, -5);
}

void BusActorItem::setTimer(QTimer *timer)
{
    timer_ = timer;
}

void BusActorItem::onPosChanged(unsigned int passenger)
{
    numPassenger = passenger;
    pLabel->setText(QString::fromStdString(std::to_string(numPassenger)));
}

unsigned int BusActorItem::getNumPassenger() const
{
    return numPassenger;
}
}
