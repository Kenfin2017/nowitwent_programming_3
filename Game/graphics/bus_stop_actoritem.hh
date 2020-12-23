#ifndef BUSSTOPACTORITEM_HH
#define BUSSTOPACTORITEM_HH

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QObject>

namespace StudentSide{
    const QString BUS_STOP_ICON_FILE = ":/images/offlinedata/bus_stop.png";
    class BusStopActorItem : public QObject, public QGraphicsPixmapItem
    {
        Q_OBJECT
    public:
        BusStopActorItem(QGraphicsItem *parent = nullptr);
//    public slots:
//        void changeState();
    private:
        int x_ = 0;
        int y_ = 0;
    };
}

#endif // BUSSTOPACTORITEM_HH
