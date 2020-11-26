#ifndef CREATEGAME_HH
#define CREATEGAME_HH

#include "core/logic.hh"
#include "gamemainwindow.hh"
#include "gamedialog.hh"
#include <QString>

/**
 * @brief The CreateGame class contains logic of the game from student side
 */

namespace StudentSide {
class CreateGame
{
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


private:
    QString gameMode = "normal"; // Normal mode - only one player
    QString playerName = "Anonymous";
    unsigned int playerScore = 0;
    unsigned int highScore;

    GameMainWindow * window;
    GameDialog * dialog;
};
}
#endif // CREATEGAME_HH
