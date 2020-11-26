#ifndef TREASURE_HH
#define TREASURE_HH
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QObject>
#include <QTimer>

namespace StudentSide {
const QString COIN_IMAGE_FILE = ":/images/offlinedata/animated_coin.png";
class Treasure : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Treasure(QGraphicsItem *parent = nullptr, QTimer* timer= nullptr, unsigned int unit = 10);

public slots:
    void onTreasureCollected();
private:
    unsigned int scoreUnit_;
    bool appear;
    QTimer* timer_;
};

}
#endif // TREASURE_HH
