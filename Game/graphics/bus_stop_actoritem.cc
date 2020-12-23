#include "bus_stop_actoritem.hh"
#include <QTimer>
namespace StudentSide{
BusStopActorItem::BusStopActorItem(QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(BUS_STOP_ICON_FILE));
    setPos(x_, y_);
    setScale(0.04);// 256x256 -> 10x10
}

}
