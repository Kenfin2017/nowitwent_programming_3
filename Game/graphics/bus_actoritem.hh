#ifndef BUSACTORITEM_H
#define BUSACTORITEM_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QObject>
#include <QTimer>
#include <QGraphicsScene>
#include <QLabel>
#include <QGraphicsProxyWidget>

namespace StudentSide{
    const QString BUS_ICON_FILE = ":/images/offlinedata/bus.png";

    class BusActorItem: public QObject , public QGraphicsPixmapItem
    {
        Q_OBJECT
    public:
        /**
         * @brief BusActorItem constructor
         * @param parent
         * @param timer
         */
        BusActorItem(QGraphicsItem * parent = nullptr, QTimer* timer = nullptr);

        /**
         * @brief setTimer
         * @pre -
         * @param timer
         */
        void setTimer(QTimer* timer);

        /**
         * @brief onPosChanged notifies that bus has changed its passenger count
         *       called by gameLogic.advanced()
         * @post bus's passenger count has updated.
         * @param passenger new passenger count
         */
        void onPosChanged(unsigned int passenger);

        /**
         * @brief getNumPassenger
         * @pre -
         * @return bus's passenger count
         */
        unsigned int getNumPassenger()const;

    private:
        QTimer* timer_;
        int x_;
        int y_;
        unsigned int numPassenger = 0;
        QGraphicsScene * pScene;
        QLabel* pLabel;

        QGraphicsProxyWidget * pProxyWidget;
    };
}
#endif // BUSACTORITEM_H
