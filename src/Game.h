
#ifndef PLATFORMER_GAME_H
#define PLATFORMER_GAME_H

#include "GameState/GameState.h"
#include "GameState/Level.h"
#include "GameState/Lobby.h"
#include "GameState/Menu.h"
#include "GameState/PlayerInit.h"
#include "Network/Client.h"
#include "Network/Server.h"
#include "Network/UserData.h"
#include "UI/Text.h"
#include <SFML/Graphics.hpp>

class Game
{
 public:
  Game(sf::RenderWindow& window, bool server);
  ~Game();
  bool init();
  void update(float dt);
  void render();
  void mouseClicked(sf::Event event);
  void mouseWheelMoved(sf::Event event);
  void keyPressed(sf::Event event);
  void keyReleased(sf::Event event);
  void TextEntered(sf::Event event);

 private:
  sf::RenderWindow& window;
  bool isServer = true;

  std::unique_ptr<Client> client = nullptr;
  std::unique_ptr<Server> server = nullptr;
  //Server server1;

  GameState::gameState gameState = GameState:: MAIN_MENU;

  sf::Font font;

  UserData userData;

  std::unique_ptr<Menu> mainMenu = nullptr;
  std::unique_ptr<PlayerInit> playerInitMenu = nullptr;
  std::unique_ptr<Lobby> lobby = nullptr;
  std::unique_ptr<Level> level = nullptr;

  unsigned int window_sizeX, window_sizeY;

  bool sendData = true;

};

#endif // PLATFORMER_GAME_H
