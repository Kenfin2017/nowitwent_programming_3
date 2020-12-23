#include "gameoverdialog.hh"
#include "ui_gameoverdialog.h"

namespace StudentSide {

GameOverDialog::GameOverDialog(QWidget *parent, unsigned int playerPoint, QString playerName) :
    QDialog(parent),
    ui(new Ui::GameOverDialog)
{
    ui->setupUi(this);
    playerScore_ = playerPoint;
    playerName_ = playerName;
    ui->playerName_label->setText(playerName_);
    ui->playerScore_label->setText(QString::fromStdString(std::to_string(playerScore_)));
}

GameOverDialog::~GameOverDialog()
{
    delete ui;
}

void GameOverDialog::setPlayerName(QString playerName)
{
    playerName_ = playerName;
    ui->playerName_label->setText(playerName_);
}

void GameOverDialog::setPlayerScore(unsigned int playerScore)
{
    playerScore_ = playerScore;
    ui->playerScore_label->setText(QString::fromStdString(std::to_string(playerScore_)));
}

}

void StudentSide::GameOverDialog::on_exit_btn_clicked()
{
    emit gameExit();
    close();
}
