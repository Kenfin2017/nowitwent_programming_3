#include "gamemainwindow.hh"
#include "ui_gamemainwindow.h"
using namespace StudentSide;
const int PADDING = 10;

GameMainWindow::GameMainWindow(QWidget *parent, QString playerName, unsigned int scoreLimit, QString mapSize) :
    QMainWindow(parent),
    ui(new Ui::GameMainWindow)
{
    ui->setupUi(this);
    //Game config info (from Gamedialog)
    playerName_ = playerName;
    maxPoints = scoreLimit;
    mapSize_ = mapSize;

    // generate scene
    map = new QGraphicsScene(this);
    ui->gameView->setScene(map);

    //Initialize game logic and city
    city = new City();
    gameLogic = new GameLogic();
    gameLogic->setCity(std::shared_ptr<City>(city));
    gameLogic->startGame();
    offlinedata_ = gameLogic->getOfflineData();

    // Generate map
    generateMap();

    // Initialize player Item
    playerItem = new PlayerActorItem();
    playerItem->setFlag(QGraphicsItem::ItemIsFocusable);
    playerItem->setZValue(2);
    playerItem->setFocus();
    playerItem->setPos(width_/2, height_/2);
    playerItem->setMaxPos(width_, height_);
    map->addItem(playerItem);

    // Add buses from gameLogic buses list

    buses = gameLogic->getBus();
    for(unsigned int i = 0; i < buses.size(); i++){
        std::shared_ptr<Nysse> bus = buses.at(i);
        BusActorItem* busItem = new BusActorItem(nullptr);
        busItem->setPos(bus->giveLocation().giveX(), bus->giveLocation().giveY());
        busItems.push_back(busItem);
        map->addItem(busItem);
    }

    // Add a random number of coins to earn points
    srand(time(NULL));
    currentPointCount = 0;
    generateCoins();

    //set score label and name label
    ui->score_label->setText(QString::fromStdString(std::to_string(playerPoint)));
    ui->name_label->setText(playerName);

    //init sound effect
    soundEffect = new QMediaPlayer(this);
    soundEffect->setVolume(100);


    //Digital clock
    timer = new QTimer(this);
    digitalTimer = new DigitalClock(this, timer);
    clock = gameLogic->getClock();

    connect(timer, &QTimer::timeout, gameLogic, &GameLogic::increaseTime);
    connect(timer, &QTimer::timeout, this, &GameMainWindow::onTimeOut);
    connect(gameLogic, &GameLogic::gameAdvanced, this, &GameMainWindow::onMovingBus);
    connect(playerItem, &PlayerActorItem::hitCoins, this, &GameMainWindow::onPlayerEarnPoint);
    connect(playerItem, &PlayerActorItem::hitBus, this, &GameMainWindow::onPlayerHitBus);
    timer->start(GameLogic::UPDATE_INTERVAL_MS);
}

void GameMainWindow::setPicture(std::shared_ptr<QImage> img)
{
    map->setBackgroundBrush(img->mirrored().scaledToHeight(height_,Qt::SmoothTransformation));
}

void GameMainWindow::setPlayerName(QString playerName)
{
    playerName_ = playerName;
}

void GameMainWindow::setMapSize(QString mapSize)
{
    mapSize_ = mapSize;
}

unsigned int GameMainWindow::playerScore() const
{
    return playerPoint;
}

GameMainWindow::~GameMainWindow()
{
    delete ui;
}

void GameMainWindow::onMovingBus()
{
    for(unsigned int i = 0; i < busItems.size(); i++){
        busItems.at(i)->setPos(buses.at(i)->giveLocation().giveX(),buses.at(i)->giveLocation().giveY());
        busItems.at(i)->onPosChanged(buses.at(i)->getPassengers().size());
    }
}

void GameMainWindow::onPlayerEarnPoint(TreasureItem* t)
{
    unsigned int pointToAdd = 0;

    qDebug() << "Player hit coin " << t->getPoint();
    //update player points
    pointToAdd = t->getPoint();
    playerPoint += pointToAdd;
    playerItem->setPoint(playerPoint);
    //step size is propotional to player point, capped at 6
    if((playerItem->stepSize_ + playerPoint/10) <= 6)
    {
        playerItem->setStepSize(playerItem->stepSize_ + playerPoint/10);
    }
    // and the score label
    ui->score_label->setText(QString::fromStdString(std::to_string(playerPoint)));

    //play sound effect
    soundEffect->setMedia(QUrl(COIN_SOUND_EFFECT));
    soundEffect->play();

    //and remove the coin from the map
    map->removeItem(t);
    t->onTreasureCollected();

    //generate more coins when only about half is left
    currentPointCount -= pointToAdd;
    if(currentPointCount < maxPoints/2){
        generateCoins();
    }

    if(playerPoint >= maxPoints){
        showGameOver();
    }
}

void GameMainWindow::onPlayerHitBus(BusActorItem *b)
{
    int pointToSubtract = 0;

    pointToSubtract = b->getNumPassenger()*10;
    if((int)playerPoint > pointToSubtract && playerItem->stepSize_ > pointToSubtract/10){
        playerPoint -= pointToSubtract;
        playerItem->setStepSize(playerItem->stepSize_- pointToSubtract/10);
    }
    else{
        playerPoint = 0;
        playerItem->setStepSize(2);
    }
    playerItem->setPoint(playerPoint);
    ui->score_label->setText(QString::fromStdString(std::to_string(playerPoint)));

    soundEffect->setMedia(QUrl(CRASH_SOUND_EFFECT));
    soundEffect->play();
}

void StudentSide::GameMainWindow::on_upArrowBtn_pressed()
{
    if(playerItem->y() > 0){
        playerItem->setDirectionAndMovingState(NORTH, true);
    }
    else{
        playerItem->setDirectionAndMovingState(NORTH, false);
    }
}

void StudentSide::GameMainWindow::on_leftArrowBtn_pressed()
{
    if(playerItem->x() >0){
        playerItem->setDirectionAndMovingState(WEST, true);
    }
    else{
        playerItem->setDirectionAndMovingState(WEST,false);
    }
}

void StudentSide::GameMainWindow::on_downArrowBtn_pressed()
{
    if(playerItem->y() < height_-25){
        playerItem->setDirectionAndMovingState(SOUTH, true);
    }
    else{
        playerItem->setDirectionAndMovingState(SOUTH, false);
    }
}

void StudentSide::GameMainWindow::on_rightArrowBtn_pressed()
{
    if(playerItem->x() < width_-20){
        playerItem->setDirectionAndMovingState(EAST, true);
    }
    else{
        playerItem->setDirectionAndMovingState(EAST, false);
    }
}

void StudentSide::GameMainWindow::on_upArrowBtn_released()
{
    playerItem->setDirectionAndMovingState(playerItem->getDirection(), false);
}

void StudentSide::GameMainWindow::on_leftArrowBtn_released()
{
    playerItem->setDirectionAndMovingState(playerItem->getDirection(), false);
}

void StudentSide::GameMainWindow::on_downArrowBtn_released()
{
    playerItem->setDirectionAndMovingState(playerItem->getDirection(), false);
}

void StudentSide::GameMainWindow::on_rightArrowBtn_released()
{
    playerItem->setDirectionAndMovingState(playerItem->getDirection(), false);
}

void GameMainWindow::onTimeOut()
{
    if(clock->hour() == 21 && clock->minute() >= 30){
        showGameOver();
    }
    digitalTimer->showTime(clock);
}

void GameMainWindow::generateMap()
{
    if(mapSize_ == "large"){
        // Load image according to size option
        width_ = 1095;
        height_ = 592;

        this->setFixedSize(width_+ ui->statistic_label->width() + ui->score_label->width() + 2* PADDING, height_ + 2*PADDING);

        ui->gameView->move(PADDING, PADDING);
        ui->gameView->setFixedSize(width_ ,height_);

        map->setSceneRect(0,0,width_,height_);

        //Arrow button's, collect_treasure button and score label's location
        ui->upArrowBtn->move(width_ + 2*PADDING + ui->upArrowBtn->width(), height_ - 6*PADDING);
        ui->downArrowBtn->move(width_ + 2*PADDING + ui->upArrowBtn->width(), height_ - 6*PADDING + ui->upArrowBtn->height());
        ui->leftArrowBtn->move(width_ + 2*PADDING , height_ - 6*PADDING + ui->upArrowBtn->height());
        ui->rightArrowBtn->move(width_ + 2*PADDING + ui->upArrowBtn->width()*2, height_ - 6*PADDING +ui->upArrowBtn->height());
        ui->statistic_label->move(width_ + 2*PADDING, 2*PADDING);
        ui->score_label->move(width_ + 2*PADDING+ ui->statistic_label->width(), 2*PADDING);
        ui->user_label->move(width_ + 2*PADDING, ui->statistic_label->height()+ 2*PADDING);
        ui->name_label->move(width_ + 2*PADDING+ ui->statistic_label->width(),ui->score_label->height()+ 2*PADDING);
        ui->quit_btn->move(width_ + 2*PADDING + 3*ui->upArrowBtn->width(), height_ - 2* PADDING - ui->quit_btn->height());
        setPicture(city->getBackground("large"));
    }
    else{
        width_ = 500;
        height_ = 500;

        this->setFixedSize(width_+ui->statistic_label->width()+ ui->score_label->width() + 2* PADDING, height_ + 2*PADDING);
        ui->gameView->move(PADDING, PADDING);
        ui->gameView->setFixedSize(width_ ,height_);
        map->setSceneRect(0,0,width_,height_);

        ui->upArrowBtn->move(width_ + 2*PADDING + ui->upArrowBtn->width(), height_ - 6*PADDING);
        ui->downArrowBtn->move(width_ + 2*PADDING + ui->upArrowBtn->width(), height_ - 6*PADDING + ui->upArrowBtn->height());
        ui->leftArrowBtn->move(width_ + 2*PADDING, height_ - 6*PADDING + ui->upArrowBtn->height());
        ui->rightArrowBtn->move(width_ + 2*PADDING + ui->upArrowBtn->width()*2, height_ - 6*PADDING +ui->upArrowBtn->height());
        ui->statistic_label->move(width_ + 2*PADDING, 2*PADDING);
        ui->score_label->move(width_ + 2*PADDING+ ui->statistic_label->width(), 2*PADDING);
        ui->user_label->move(width_ + 2*PADDING, ui->statistic_label->height()+ 2*PADDING);
        ui->name_label->move(width_ + 2*PADDING+ ui->statistic_label->width(),ui->score_label->height()+ 2*PADDING);
        ui->quit_btn->move(width_ + 2*PADDING + 3*ui->upArrowBtn->width(), height_ - 2* PADDING - ui->quit_btn->height());
        setPicture(city->getBackground("small"));
    }
}

void GameMainWindow::showGameOver()
{
    emit gameOver(playerPoint, playerName_);
    close();
}

void GameMainWindow::generateCoins()
{
    srand(time(NULL));
    unsigned int randPoint, treasureX, treasureY;

    while(currentPointCount < maxPoints){
        randPoint = (rand() % 4) * 10;
        treasureX = rand() % width_ - PADDING;
        treasureY = rand() % height_ - PADDING;
        TreasureItem * item = new TreasureItem();
        item->setPoint(randPoint);
        item->setPos(treasureX, treasureY);
        currentPointCount += randPoint;
        treasureItems.push_back(item);
        map->addItem(item);
    }
}

void GameMainWindow::on_quit_btn_clicked()
{
    close();
}

