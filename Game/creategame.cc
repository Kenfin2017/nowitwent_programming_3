#include "creategame.hh"
namespace StudentSide {
CreateGame::CreateGame()
{
    Initialize();

    connect(window, &GameMainWindow::gameOver, this, &CreateGame::onMainWindowClose);
}

CreateGame::~CreateGame()
{
    qDebug() << "game exited" ;
}

void CreateGame::Initialize()
{
    musicPlayer = new QMediaPlaylist();
    musicPlayer->addMedia(QUrl(GAME_AUDIO_FILE));
    musicPlayer->setPlaybackMode(QMediaPlaylist::Loop);

    mediaPlayer = new QMediaPlayer();
    mediaPlayer->setPlaylist(musicPlayer);
    mediaPlayer->setVolume(50); // adjust to 50% volume
    mediaPlayer->play();

    dialog = new GameDialog();

    if(dialog->exec() == QDialog::Accepted){
        window = new GameMainWindow(nullptr, dialog->getPlayerName(), dialog->getScoreLimit(), dialog->getSize());
        playerName = dialog->getPlayerName();
        scoreLimit = dialog->getScoreLimit();
        mapSize = dialog->getSize();
        window->show();
        qDebug() << "game created";
    }
    else{
        qDebug() << "game creation fail";
        if(window->close()){
            qDebug() << "game exit success";
        }
        else{
            qDebug() << "error exiting program";
        }
    }
}

void CreateGame::onMainWindowClose(unsigned int point, QString name)
{
    gameOverDialog = new GameOverDialog(nullptr, point, name);

    playerScore = point;

    gameOverDialog->show();
}

}
