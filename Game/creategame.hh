#ifndef CREATEGAME_HH
#define CREATEGAME_HH

#include "core/logic.hh"
#include "core/city.hh"
#include "graphics/simplemainwindow.hh"
#include <QString>
using namespace StudentSide;

/**
 * @brief The CreateGame class contains logic of the game from student side
 */
class CreateGame
{
public:
    /**
     * @brief CreateGame
     */
    CreateGame();
    ~CreateGame();

    /**
     * @brief Initialize the game play
     * @post Game view is created
     * @exception no throw
     */
    void Initialize();

    /**
     * @brief Show Dialog window
     * @post After dialog window is close, gamemode is initialized
     */
    void Dialog();


private:
    QString gameMode = "normal"; // Normal mode - only one player
    QString playerName = "Anonymous";
    unsigned int playerScore = 0;
    unsigned int highScore;

    SimpleMainWindow *window;
};

#endif // CREATEGAME_HH
