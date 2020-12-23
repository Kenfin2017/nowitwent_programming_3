#include "treasureItem.hh"

namespace StudentSide{

TreasureItem::TreasureItem(QGraphicsItem *parent, QTimer *timer, unsigned int point):
    QObject(),
    QGraphicsPixmapItem(parent),
    timer_(timer)
{
    collected = false;
    setPoint(point);
}


void TreasureItem::setPoint(unsigned int point)
{
    pointUnit_ = point;
    switch(point){
    case 10:
        setPixmap(QPixmap(COIN_IMAGE_FILE).scaledToWidth(20));
        break;
    case 20:
        setPixmap(QPixmap(COIN_IMAGE_FILE).scaledToWidth(20));
        break;
    case 30:
        setPixmap(QPixmap(COIN_IMAGE_FILE).scaledToWidth(30));
        break;
    case 40:
        setPixmap(QPixmap(COIN_IMAGE_FILE).scaledToWidth(40));
        break;
    default:
        setPixmap(QPixmap(COIN_IMAGE_FILE).scaled(0,0, Qt::KeepAspectRatio));
        break;
    }
}

unsigned int TreasureItem::getPoint() const
{
    return pointUnit_;
}

void TreasureItem::onTreasureCollected()
{
    collected = true;
    delete this;
}

void TreasureItem::onTimeout()
{
    delete this;
}


}
