#include "gamemainwindow.hh"
#include "ui_gamemainwindow.h"
using namespace StudentSide;
const int PADDING = 10;

GameMainWindow::GameMainWindow(QWidget *parent, QString playerName, bool hardMode, QString mapSize) :
    QMainWindow(parent),
    ui(new Ui::GameMainWindow)
{
    ui->setupUi(this);
    //Game config info (from Gamedialog)
    playerName_ = playerName;
    hardMode_ = hardMode;
    mapSize_ = mapSize;

    // generate scene
    map = new QGraphicsScene(this);
    ui->gameView->setScene(map);

    //Initialize game logic and city
    city = new City();
    gameLogic = new GameLogic();
    gameLogic->startGame();

    // Generate map
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
        ui->collectTreasure_btn->move(width_ + 2*PADDING , height_ - 6*PADDING - 2*ui->upArrowBtn->height());
        ui->statistic_label->move(width_ + 2*PADDING, 2*PADDING);
        ui->score_label->move(width_ + 2*PADDING+ ui->statistic_label->width(), 2*PADDING);
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
        ui->collectTreasure_btn->move(width_ + 2*PADDING , height_ - 6*PADDING - 2*ui->upArrowBtn->height());
        ui->statistic_label->move(width_ + 2*PADDING, 2*PADDING);
        ui->score_label->move(width_ + 2*PADDING+ ui->statistic_label->width(), 2*PADDING);
        setPicture(city->getBackground("small"));
    }

    playerItem = new PlayerActorItem();
    playerItem->setFlag(QGraphicsItem::ItemIsFocusable);
    playerItem->setFocus();

    map->addItem(playerItem);

    map->setFocusItem(playerItem);
    timer = new QTimer(this);

    connect(timer, SIGNAL(timeout()),map, SLOT(advance()));
    timer->start(1000);
}

void GameMainWindow::setPicture(std::shared_ptr<QImage> img)
{
    map->setBackgroundBrush(img->mirrored().scaledToHeight(height_,Qt::SmoothTransformation));
}

GameMainWindow::~GameMainWindow()
{
    delete ui;
}

void GameMainWindow::on_collectTreasure_btn_clicked()
{
    emit collectTreasure();
    qDebug() << "Treasure collected";
}

//void GameMainWindow::onKeyPressed(QKeyEvent *event)
//{
//    playerItem->moveOnKeyPressEvent(event);
//}

void StudentSide::GameMainWindow::on_upArrowBtn_pressed()
{
    playerItem->setDirectionAndMovingState(1, true);
}

void StudentSide::GameMainWindow::on_leftArrowBtn_pressed()
{
    playerItem->setDirectionAndMovingState(3, true);
}

void StudentSide::GameMainWindow::on_downArrowBtn_pressed()
{
    playerItem->setDirectionAndMovingState(2, true);
}

void StudentSide::GameMainWindow::on_rightArrowBtn_pressed()
{
    playerItem->setDirectionAndMovingState(4, true);
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
