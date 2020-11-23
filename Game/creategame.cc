#include "creategame.hh"

CreateGame::CreateGame()
{
    Initialize();

}

CreateGame::~CreateGame()
{
    qDebug() << "game exited" ;
}

void CreateGame::Initialize()
{
    dialog = new GameDialog();
    if(dialog->exec() == QDialog::Accepted){ // if dialog receive accept signal
        // Initialize main window with configurations from GameDialog window
        window = new SimpleMainWindow(nullptr ,dialog->getPlayerName(),dialog->getGameMode(), dialog->getSize());
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

