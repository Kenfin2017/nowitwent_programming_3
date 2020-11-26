#ifndef GAMEMAINWINDOW_HH
#define GAMEMAINWINDOW_HH

#include "gamelogic.hh"
#include "city.hh"
#include "graphics/player_actoritem.hh"
#include "graphics/bus_actoritem.hh"
#include "graphics/bus_stop_actoritem.hh"
#include "treasure.hh"

#include <QMainWindow>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>

namespace Ui {
class GameMainWindow;
}
namespace StudentSide{
class GameMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameMainWindow(QWidget *parent = 0, QString playerName = "", bool hardMode = false, QString mapSize="large");
    ~GameMainWindow();

    void setPicture(std::shared_ptr<QImage> img);

signals:
    void gameStarted();
    void collectTreasure();
//     int keyPressed(Qt::Key key);
public slots:

    void on_collectTreasure_btn_clicked();
private slots:

    void on_upArrowBtn_pressed();

    void on_leftArrowBtn_pressed();

    void on_downArrowBtn_pressed();

    void on_rightArrowBtn_pressed();

    void on_upArrowBtn_released();

    void on_leftArrowBtn_released();

    void on_downArrowBtn_released();

    void on_rightArrowBtn_released();

private:

    Ui::GameMainWindow *ui;
    QGraphicsScene *map;
    QTimer *timer;
    QVector<QGraphicsItem*> actors_;

    QString playerName_;
    bool hardMode_;
    QString mapSize_;

    int width_ = 1000; //pxls
    int height_ = 650;
    int tick_ = 500; //ms
    GameLogic * gameLogic;
    City * city;
    PlayerActorItem* playerItem;
    BusActorItem* busItem;
};
}
#endif // GAMEMAINWINDOW_HH
