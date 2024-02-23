//
// Created by OscarNg on 2023/10/21.
//
#include "../Camera/Camera.h"
#include "../Network/UserData.h"
#include "../Tilemap/Tilemap.h"
#include "../UI/Text.h"
#include "Character.h"

#ifndef SFMLGAME_PLAYER_H
#define SFMLGAME_PLAYER_H

class Player : public Character
{
 public:
  enum Weapon
  {
    EMPTY,
    KNIFE,
    PISTOL
  };

  Player();
  Player(int playerID,std::string& username, UserData::characterSkin skin ,const sf::Font& font, Tilemap& map);
  Player(int playerID,std::string& username, UserData::characterSkin skin);
  ~Player() = default;
  void init(std::string& username,UserData::characterSkin skin, const sf::Font& font, float posX, float posY, unsigned int windowSizeX, unsigned int windowSizeY);
  void update(Tilemap& tilemap,float dt);
  void animation(UserData::movingDir playerDirection);
  void keyPressed(sf::Event event);
  void keyReleased(sf::Event event);

  UserData& getUserdata();

  UserData::movingDir getPlayerDir();

  std::unique_ptr<Camera>& getCamera();

  std::unique_ptr<Text>& getNameText();

  void setSpawned(bool boolean);

  bool getSpawned();

 private:
  std::unique_ptr<sf::Texture> character_texture= nullptr;
  std::unique_ptr<sf::IntRect> character_texture_rect= nullptr;
  std::unique_ptr<sf::Clock> character_anim_clock = nullptr;

  std::unique_ptr<Text> username_text= nullptr;
  std::unique_ptr<Camera> camera= nullptr;

  bool isMovingUp = false;
  bool isMovingDown = false;
  bool isMovingLeft = false;
  bool isMovingRight = false;

  bool isSpawned = false;

  UserData playerData;

  UserData::movingDir playerDir = UserData::NONE;

  Weapon weaponUsing = EMPTY;
};

#endif // SFMLGAME_PLAYER_H
