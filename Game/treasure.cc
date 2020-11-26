#include "treasure.hh"

namespace StudentSide{

Treasure::Treasure(QGraphicsItem* parent, QTimer* timer, unsigned int unit): QObject(), QGraphicsPixmapItem(parent)
{
    timer_ = timer;
    switch(unit){
    case 10:
        setPixmap(QPixmap(COIN_IMAGE_FILE).scaled(10,10, Qt::KeepAspectRatio));
        break;
    case 20:
        setPixmap(QPixmap(COIN_IMAGE_FILE).scaled(15,15, Qt::KeepAspectRatio));
        break;
    case 40:
        setPixmap(QPixmap(COIN_IMAGE_FILE).scaled(25,25, Qt::KeepAspectRatio));
        break;
    default:
        setPixmap(QPixmap(COIN_IMAGE_FILE).scaled(0,0, Qt::KeepAspectRatio));
        break;
    }

}

void Treasure::onTreasureCollected()
{
    delete this;
}
}
