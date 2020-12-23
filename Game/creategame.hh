#ifndef CREATEGAME_HH
#define CREATEGAME_HH

#include "core/logic.hh"
#include "graphics/gamemainwindow.hh"
#include "graphics/gamedialog.hh"
#include "graphics/gameoverdialog.hh"
#include <QMediaPlaylist>
#include <QMediaPlayer>
#include <QString>

/**
 * @brief The CreateGame class contains logic of the game from student side
 */

namespace StudentSide {
const QString GAME_AUDIO_FILE = "qrc:/audio/offlinedata/Sim_City-The_Card_Game.mp3";
class CreateGame : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief CreateGame constructor
     */
    CreateGame();

    /**
     * @brief CreateGame destructor
     */
    ~CreateGame();

    /**
     * @brief Initialize the game play
     * @post If dialog return accepted, Game view is created, exits otherwise
     * @exception no throw
     */
    void Initialize();
private slots:
    /**
     * @brief onMainWindowClose recognize gameOver signal from GameMainWindow
     * @param point player's point
     * @param name player's name
     * @post show a GameOverDialog window which display player's name and score
     */
    void onMainWindowClose(unsigned int point, QString name);

private:
    QString playerName = "Anonymous";
    QString mapSize;
    unsigned int scoreLimit = 100;
    unsigned int playerScore = 0;
    unsigned int highScore;

    GameMainWindow * window;
    GameDialog * dialog;
    GameOverDialog * overDialog;
    GameOverDialog* gameOverDialog;

    // allow mediaplayer to play music with mediaPlaylist in a loop
    QMediaPlayer* mediaPlayer;
    QMediaPlaylist* musicPlayer;
};
}
#endif // CREATEGAME_HH
