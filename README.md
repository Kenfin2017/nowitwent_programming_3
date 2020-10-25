#### Game Overview

##### Goals
- The player who score higher than others after each gameplay wins. Scores are earned by:
+ Collect passengers at terminals (propotional to how many passengers collected at the terminal, the more busy at the terminal, the higher the score)
+ Arrive at terminal on time (the earlier, the more points you will earn)

##### Use Cases
- The game starts with the help of a self-implemented main program. The game asks with a separate configuration window the number of players and other information needed by the game. After this the main window implemented by the group is opened. On it, there is the game board with the map, the players gamepieces and other necessary information.
- The given implementation produces buses onto the map and moves them according to their schedules. On the busstops, passenger get on and off the busses.
- The player starts the game by clicking a game piece in the main window.
- The player moves their playable figure with the arrow keys to move toward a close-by bus that just picked up a couple of passengers.
- The player shoot at the bus with a stun gun. When hit, the bus stops and turns pink. The passengers on the bus need to walk.
- The player seeks new busses as their target. In the main window statistics about the stuck busses and the passenger on foor is show.
- The game ends after five minutes of gameplay and the final score is shown to the player.
- The player closes the game.