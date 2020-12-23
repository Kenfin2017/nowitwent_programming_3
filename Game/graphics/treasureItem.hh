#ifndef TREASURE_HH
#define TREASURE_HH
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QObject>
#include <QTimer>
#include "player_actoritem.hh"

namespace StudentSide {
const QString COIN_IMAGE_FILE = ":/images/offlinedata/animated_coins.png";
class TreasureItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    TreasureItem(QGraphicsItem* parent = nullptr, QTimer* timer = 0, unsigned int point = 10);
    /**
     * @brief setPoint set the point units of the TreasureItem
     * @pre point > 0
     * @param point value of treasure
     */
    void setPoint(unsigned int point);

    /**
     * @brief getPoint return pointUnit_ of TreasureItem
     * @return
     */
    unsigned int getPoint() const;

    /**
     * @brief onTreasureCollected is called when PlayerItem collide with the object
     * @post delete itself from the game and set collected = true
     */
    void onTreasureCollected();

public slots:    
    void onTimeout();

private:
    unsigned int pointUnit_;
    bool collected;
    QTimer* timer_;
};

}
#endif // TREASURE_HH
