//
// Created by OscarNg on 2023/12/2.
//

#ifndef SFMLGAME_GAMESTATE_H
#define SFMLGAME_GAMESTATE_H

class GameState
{
 public:
  enum gameState {
    MAIN_MENU,
    PLAYER_INIT,
    LOBBY,
    GUIDE,
    IN_GAME,
    GAME_WON,
    GAME_OVER
  };

};

#endif // SFMLGAME_GAMESTATE_H
