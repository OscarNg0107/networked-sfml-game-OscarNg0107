//
// Created by OscarNg on 2023/10/20.
//
#include <SFML/Graphics.hpp>
#ifndef SFMLGAME_LOBBY_H
#define SFMLGAME_LOBBY_H

#  include "../Camera/Camera.h"
#  include "../GameObjects/Player.h"
#  include "../Network/Client.h"
#  include "../Network/UserData.h"
#  include "../Tilemap/Tilemap.h"
#  include "../UI/Chatroom.h"
#  include "../UI/PauseMenu.h"

class Lobby : public sf::Drawable
{
 public:
  Lobby();
  ~Lobby() = default;
  void init(std::string& player_name, UserData::characterSkin player_skin,unsigned int windowSizeX, unsigned int windowSizeY, const sf::Font& font);
  void update(float dt, Client& client , const sf::Font& font, std::vector<std::shared_ptr<UserData>>& otherplayersData);
  void mouseWheelMoved(sf::Event event);
  int keyPressed(sf::Event event,std::string& username, Client& client, const sf::Font& font);
  void keyReleased(sf::Event event);
  void TextEntered(sf::Event event);
  void resetLobbyData();

  bool test = false;
  bool isStartGame();
  void setIsStartGame(bool boolean);

 private:
  virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

  std::unique_ptr<Tilemap> map_lobby;

  std::unique_ptr<Player> player;
  std::vector<std::unique_ptr<Player>> otherplayers;
  std::unique_ptr<Chatroom> chatroom;
  std::unique_ptr<PauseMenu> pauseMenu = nullptr;

  bool startGame = false;

};

#endif // SFMLGAME_LOBBY_H
