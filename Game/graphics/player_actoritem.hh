#ifndef PLAYERACTORITEM_HH
#define PLAYERACTORITEM_HH

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QObject>
#include <QKeyEvent>
#include <QDebug>
#include <QTimer>
#include "treasureItem.hh"
#include "bus_actoritem.hh"

namespace StudentSide{
    const QString PLAYER_FACE_NORTH_FILE =":/player_images/offlinedata/player-face-north.png";
    const QString PLAYER_FACE_SOUTH_FILE =":/player_images/offlinedata/player-face-south.png";
    const QString PLAYER_FACE_WEST_FILE =":/player_images/offlinedata/player-face-west.png";
    const QString PLAYER_FACE_EAST_FILE =":/player_images/offlinedata/player-face-east.png";
    const QString PLAYER_GOES_NORTH_FILE =":/player_images/offlinedata/player-goes-north.png";
    const QString PLAYER_GOES_SOUTH_FILE =":/player_images/offlinedata/player-goes-south.png";
    const QString PLAYER_GOES_EAST_FILE =":/player_images/offlinedata/player-goes-east.png";
    const QString PLAYER_GOES_WEST_FILE =":/player_images/offlinedata/player-goes-west.png";

    enum DIRECTION {NORTH = 1, SOUTH = 2, WEST = 3, EAST = 4};
    class TreasureItem;
    class PlayerActorItem : public QObject, public QGraphicsPixmapItem
    {
        Q_OBJECT
        public:
            PlayerActorItem(QGraphicsItem* parent = nullptr);

            /**
             * @brief setDirectionAndMovingState set the playerItem moving state and direction
             * @pre PlayerItem is created
             * @param dir DIRECTION
             * @param moving tells whether playerItem is moving or not
             * @post player location changes if moving is true and sets its image according to
             * the given dir and moving state
             */
            void setDirectionAndMovingState(DIRECTION dir, bool moving);

            /**
             * @brief move
             * @param dir DIRECTION
             * @post playerItem relocate by stepSize according to the given dir
             */
            void move(DIRECTION dir);

            /**
             * @brief setStepSize set the amount of displacement everytime it move
             * @param stepSize size of step
             */
            void setStepSize(int stepSize);

            /**
             * @brief getDirection get the current direction of PlayerItem
             * @return direction_
             */
            DIRECTION getDirection() const;

            /**
             * @brief setMaxPos sets the maximum limit for PlayerItem's x and y value
             * @param max_x
             * @param max_y
             */
            void setMaxPos(int max_x, int max_y);

            /**
             * @brief setPoint sets the current point of player
             * @param p point
             */
            void setPoint(unsigned int p);

            /**
             * @brief getPoint returns the player's point
             * @return point
             */
            unsigned int getPoint()const;

            /**
             * @brief getMovingState return playerItem's moving state
             * @return moving_
             */
            bool getMovingState() const;
            int stepSize_ = 2;
    public slots:
            /**
             * @brief keyPressEvent recognize arrow key press events, which sets
             * the PlayerItem's direction and moving state to true
             * @pre event->getKey() is KeyUp | KeyDown | KeyLeft | KeyRight
             * @param event QKeyEvent
             */
            void keyPressEvent(QKeyEvent *event);

            /**
             * @brief keyReleaseEvent recognize arrow key press events, which sets
             * the PlayerItem's direction and moving state to false
             * @pre event->getKey() is KeyUp | KeyDown | KeyLeft | KeyRight
             * @param event QKeyEvent
             */
            void keyReleaseEvent(QKeyEvent *event);

    signals:
            /**
             * @brief hitCoins signal GameMainWindow the treasureItem that it collide with
             * @param t TreasureItem
             */
            void hitCoins(TreasureItem* t);

            /**
             * @brief hitBus signal GameMainWindow the BusItem that it collides with
             * @param b BusActorItem
             */
            void hitBus(BusActorItem* b);
        private:
            int x_ = 500;
            int y_ = 250;
            int max_x_;
            int max_y_;
            bool moving_;

            unsigned int point;
            QTimer* timer;
            // direction of the player
            DIRECTION direction_;
    };

}
#endif // PLAYERACTORITEM_HH
