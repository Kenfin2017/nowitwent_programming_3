#ifndef GAMEMAINWINDOW_HH
#define GAMEMAINWINDOW_HH

#include "core/gamelogic.hh"
#include "core/city.hh"
#include "graphics/player_actoritem.hh"
#include "graphics/bus_actoritem.hh"
#include "treasureItem.hh"
#include "graphics/gameoverdialog.hh"
#include "graphics/digitalclock.hh"
#include "graphics/gamedialog.hh"
#include <QMainWindow>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QMediaPlayer>

namespace Ui {
class GameMainWindow;
}
namespace StudentSide{

const QString COIN_SOUND_EFFECT = "qrc:/audio/offlinedata/Bag-of-Coins-B.mp3";
const QString CRASH_SOUND_EFFECT = "qrc:/audio/offlinedata/mixkit-boxer-getting-hit.mp3";
class GameMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameMainWindow(QWidget *parent = 0, QString playerName = "s", unsigned int scoreLimit = 100, QString mapSize="large");
    ~GameMainWindow();

    /**
     * @brief setPicture set scene's image
     * @pre img is valid
     * @param img
     * @post new image is loaded
     */
    void setPicture(std::shared_ptr<QImage> img);

    /**
     * @brief setPlayerName set player name to display
     * @pre -
     * @param playerName
     * @post playerName is set
     */
    void setPlayerName(QString playerName);

    /**
     * @brief setMapSize
     * @pre mapSize should be either "small" or "large"
     * @param mapSize
     * @post set value of mapSize
     */
    void setMapSize(QString mapSize);

    /**
     * @brief playerScore
     * @return player's score
     */
    unsigned int playerScore() const;
signals:
    void gameStarted();
    void gameOver(unsigned int point, QString name);

    void BusChanged(unsigned int passenger);

public slots:

    void onMovingBus();

    /**
     * @brief onPlayerEarnPoint called by hitCoin() signal from PlayerItem
     * @param t coin object that playerItem hits
     */
    void onPlayerEarnPoint(TreasureItem* t);

    /**
     * @brief onPlayerHitBus called by hitBus() signal from PlayerItem
     * @param b bus object that playerItem hits
     */
    void onPlayerHitBus(BusActorItem* b);
private slots:

    // arrow button effects pressed => moving, release => not moving
    void on_upArrowBtn_pressed();

    void on_leftArrowBtn_pressed();

    void on_downArrowBtn_pressed();

    void on_rightArrowBtn_pressed();

    void on_upArrowBtn_released();

    void on_leftArrowBtn_released();

    void on_downArrowBtn_released();

    void on_rightArrowBtn_released();

    // update clock time
    void onTimeOut();

    void on_quit_btn_clicked();

private:
    // generate gameView with the map's loaded image
    void generateMap();
    // emits gameOver() signal
    void showGameOver();
    // renew number of coin in the map
    void generateCoins();

    Ui::GameMainWindow *ui;
    QGraphicsScene *map;
    // Timer and clock
    QTimer *timer;
    QTime* clock;
    QVector<QGraphicsItem*> actors_;

    QString playerName_;

    QString mapSize_;

    int width_ = 1000; //pxls
    int height_ = 650;

    unsigned int maxPoints;
    unsigned int currentPointCount;
    GameLogic * gameLogic;
    std::shared_ptr<OfflineData> offlinedata_;
    std::vector<std::shared_ptr<Nysse>> buses;
    City* city;

    //graphical items
    PlayerActorItem* playerItem;
    std::vector<BusActorItem*> busItems;
    std::vector<TreasureItem*> treasureItems;
    DigitalClock* digitalTimer;

    unsigned int playerPoint = 0;

    QMediaPlayer* soundEffect;
};
}
#endif // GAMEMAINWINDOW_HH
