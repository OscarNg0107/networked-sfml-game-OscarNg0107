
#include "Game.h"
#include <iostream>
#include <tmxlite/Map.hpp>
#include <math.h>

Game::Game(sf::RenderWindow& game_window, bool server)
  : window(game_window), isServer(server)
{
  srand(time(NULL));
}

Game::~Game()
{

}

bool Game::init()
{

  if(isServer)
  {
    /*server1.init();
    server1.run();*/
    server = std::make_unique<Server>();
    server ->init();
    server ->run();
  }
  else
  {
    client = std::make_unique<Client>();
    //client-> connect();
  }

  window_sizeX = window.getSize().x;
  window_sizeY = window.getSize().y;

  if (!font.loadFromFile("Data/Fonts/OpenSans-Bold.ttf"))
  {
    std::cout << "font loading error";
  }

  mainMenu = std::make_unique<Menu>();
  playerInitMenu = std::make_unique<PlayerInit>();
  lobby = std::make_unique<Lobby>();
  level = std::make_unique<Level>();


  mainMenu->init(font, window_sizeX, window_sizeY);
  playerInitMenu->init(font, window_sizeX, window_sizeY);

  return true;
}

void Game::update(float dt)
{
  window_sizeX = window.getSize().x;
  window_sizeY = window.getSize().y;
  if(gameState == GameState::MAIN_MENU)
  {
    mainMenu->update();
    if(mainMenu->getStartBool())
    {
      gameState = GameState::PLAYER_INIT;
      mainMenu->setStartBool(false);
    }
    if(mainMenu->getQuitBool())
    {
      window.close();
    }
  }
  if(gameState == GameState::PLAYER_INIT)
  {
    playerInitMenu->update(window_sizeX, window_sizeY);

    if(playerInitMenu->getPressEnterBool())
    {
      client-> connect();
      client->gameState = GameState::LOBBY;
      client->sendPlayerData(userData.getUserName(), userData.getCharSkin());
      gameState =GameState:: LOBBY;
      playerInitMenu->setPressEnterBool(false);
    }
  }

  if(gameState == GameState::LOBBY)
  {
    lobby->update(dt, *client, font, client->otherplayersData);
    if(lobby->isStartGame())
    {
      userData.setExitCurrentGame(true);
      if(sendData)
      {
        client->gameState = GameState::IN_GAME;
        client->sendEnterGame(userData.getUserName(), userData.getCharSkin(), userData.getExitCurrentGame(), userData.getNumOfKills());
        client->myHealth = userData.getHealth();
        sendData = false;
      }
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
      //need to confirm that the client got the data before running the following code
      level->init(userData.getUserName(),userData.getCharSkin(),client->spawnID, window_sizeX,window_sizeY,font);
      std::cout << "SpawnID: " << client->spawnID << std::endl;
      gameState = GameState::IN_GAME;
      userData.setExitCurrentGame(false);
      lobby->setIsStartGame(false);
    }

  }

  if(gameState == GameState::IN_GAME)
  {
    level->update(dt, *client, font);
  }
}

void Game::render()
{
  //rendering goes here
  if(gameState ==GameState:: MAIN_MENU)
  {
    window.draw(*mainMenu);
  }
  if(gameState ==GameState:: PLAYER_INIT)
  {
    window.draw(*playerInitMenu);
  }

  if(gameState == GameState::LOBBY)
  {
    window.draw(*lobby);
  }

  if(gameState == GameState::IN_GAME)
  {
    window.draw(*level);
  }
}

void Game::mouseClicked(sf::Event event)
{
  //get the click position
  sf::Vector2i click = sf::Mouse::getPosition(window);
  sf::Vector2 translated_pos = window.mapPixelToCoords(click);
  if(gameState == GameState::PLAYER_INIT)
  {
    playerInitMenu->mouseClicked(event, translated_pos.x, translated_pos.y);
  }

  if(gameState == GameState::IN_GAME)
  {
    level->mouseClicked(event, *client,translated_pos.x, translated_pos.y);
  }
}

void Game::mouseWheelMoved(sf::Event event)
{
  if(gameState == GameState::LOBBY)
  {
    lobby->mouseWheelMoved(event);
  }
}
void Game::keyPressed(sf::Event event)
{
  if(gameState == GameState::MAIN_MENU)
  {
    mainMenu->keyPressed(event);
  }

  if(gameState == GameState::PLAYER_INIT)
  {
    playerInitMenu->keyPressed(event);
    userData.setUserName(playerInitMenu->getUsername());
    userData.setCharSkin(playerInitMenu->getCharSkinEnum());
    lobby->init(userData.getUserName(), userData.getCharSkin(), window_sizeX, window_sizeY, font);
  }

  if(gameState == GameState::LOBBY)
  {
    int lobbyReturnValue = lobby->keyPressed(event ,userData.getUserName(), *client, font);
    if(lobbyReturnValue == 1)
    {
      client->sendPlayerDisconnect();
      //client->disconnect();
      lobby->resetLobbyData();
      gameState = GameState::MAIN_MENU;
    }
    else if(lobbyReturnValue == 2)
    {
      window.close();
    }
  }

  if(gameState == GameState::IN_GAME)
  {
    int levelReturnValue = level->keyPressed(event ,userData.getUserName(), *client, font);
    if(levelReturnValue == 1)
    {
      client->sendPlayerDisconnect();
      //client->disconnect();
      gameState = GameState::MAIN_MENU;
    }
    else if(levelReturnValue == 2)
    {
      window.close();
    }
  }
}

void Game::keyReleased(sf::Event event)
{
  if(gameState == GameState::MAIN_MENU)
  {
    mainMenu->keyReleased(event);
  }

  if(gameState == GameState::LOBBY)
  {
    lobby->keyReleased(event);
  }

  if(gameState == GameState::IN_GAME)
  {
    level->keyReleased(event);
  }
}

void Game::TextEntered(sf::Event event)
{
  if(gameState == GameState::PLAYER_INIT)
  {
    playerInitMenu->TextEntered(event);
  }

  if(gameState == GameState:: LOBBY)
  {
    lobby->TextEntered(event);
  }

  if(gameState== GameState::IN_GAME)
  {
    level->TextEntered(event);
  }
}



