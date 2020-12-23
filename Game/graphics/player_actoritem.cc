#include "player_actoritem.hh"
#include "gamemainwindow.hh"
namespace StudentSide{

PlayerActorItem::PlayerActorItem(QGraphicsItem* parent): QObject(), QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(PLAYER_FACE_SOUTH_FILE));
    setPos(x_, y_);
    setScale(0.05); // 392x500 -> ~20x25

    moving_ = false;
    direction_ = SOUTH;

    point = 0;
    timer = new QTimer(this);
}

void PlayerActorItem::setDirectionAndMovingState(DIRECTION dir, bool moving)
{
    moving_ = moving;
    if(moving_){
        move(dir);
    }
    else{
        switch(direction_){
        case NORTH:
            setPixmap(QPixmap(PLAYER_FACE_NORTH_FILE));
            break;
        case SOUTH:
            setPixmap(QPixmap(PLAYER_FACE_SOUTH_FILE));
            break;
        case WEST:
            setPixmap(QPixmap(PLAYER_FACE_WEST_FILE));
            break;
        case EAST:
            setPixmap(QPixmap(PLAYER_FACE_EAST_FILE));
            break;
        }
    }
}

void PlayerActorItem::move(DIRECTION dir)
{
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i){
        auto& r = *colliding_items[i];
        if (typeid(r) == typeid(TreasureItem)){
            TreasureItem* treasureObj = dynamic_cast<TreasureItem*>(colliding_items[i]);
            emit hitCoins(treasureObj);
        }
        else if (typeid(r) == typeid(BusActorItem)){
            BusActorItem* busObj = dynamic_cast<BusActorItem*>(colliding_items[i]);
            emit hitBus(busObj);
        }
    }

    switch(dir){
    case NORTH:
        setPixmap(QPixmap(PLAYER_GOES_NORTH_FILE));
        setPos(x(), y() - stepSize_);
        break;
    case SOUTH:
        setPixmap(QPixmap(PLAYER_GOES_SOUTH_FILE));
        setPos(x(), y() + stepSize_);
        break;
    case WEST:
        setPixmap(QPixmap(PLAYER_GOES_WEST_FILE));
        setPos(x() - stepSize_, y());
        break;
    case EAST:
        setPixmap(QPixmap(PLAYER_GOES_EAST_FILE));
        setPos(x() + stepSize_, y());
        break;
    }
}

void PlayerActorItem::setStepSize(int stepSize)
{
    stepSize_ = stepSize;
}

DIRECTION PlayerActorItem::getDirection() const
{
    return direction_;
}

void PlayerActorItem::setMaxPos(int max_x, int max_y)
{
    max_x_ = max_x;
    max_y_ = max_y;
}

void PlayerActorItem::setPoint(unsigned int p)
{
    point = p;
}

unsigned int PlayerActorItem::getPoint() const
{
    return point;
}

bool PlayerActorItem::getMovingState() const
{
    return moving_;
}

void PlayerActorItem::keyPressEvent(QKeyEvent* event)
{

    if(event->key() == Qt::Key_Left){
        if(x() > 0){
            setDirectionAndMovingState(WEST, true);
        }
        else{
            setDirectionAndMovingState(WEST, false);
        }
    }
    else if(event->key() == Qt::Key_Right){
        if(x() < (max_x_-20)){
            setDirectionAndMovingState(EAST, true);
        }
        else{
            setDirectionAndMovingState(EAST, false);
        }
    }
    else if(event->key() == Qt::Key_Up){
        if(y() > 0){
            setDirectionAndMovingState(NORTH, true);
        }
        else{
            setDirectionAndMovingState(NORTH, false);
        }
    }
    else if(event->key() == Qt::Key_Down){
        if(y() < (max_y_-25)){
            setDirectionAndMovingState(SOUTH, true);
        }
        else{
            setDirectionAndMovingState(SOUTH, false);
        }
    }
}

void PlayerActorItem::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Up){
        setPixmap(QPixmap(PLAYER_FACE_NORTH_FILE));
        moving_ = false;
    }
    else if(event->key() == Qt::Key_Down){
        setPixmap(QPixmap(PLAYER_FACE_SOUTH_FILE));
        moving_ = false;
    }
    else if(event->key() == Qt::Key_Left){
        setPixmap(QPixmap(PLAYER_FACE_WEST_FILE));
        moving_ = false;
    }
    else if(event->key() == Qt::Key_Right){
        setPixmap(QPixmap(PLAYER_FACE_EAST_FILE));
        moving_ = false;
    }
}

}
