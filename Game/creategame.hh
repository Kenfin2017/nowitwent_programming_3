#ifndef CREATEGAME_HH
#define CREATEGAME_HH

#include "core/logic.hh"
#include "graphics/simplemainwindow.hh"
#include "gamedialog.hh"
#include <QString>
using namespace StudentSide;

/**
 * @brief The CreateGame class contains logic of the game from student side
 */
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

    SimpleMainWindow * window;
    GameDialog * dialog;
};

#endif // CREATEGAME_HH
