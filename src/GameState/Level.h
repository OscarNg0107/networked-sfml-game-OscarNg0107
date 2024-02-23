//
// Created by OscarNg on 2023/10/28.
//

#ifndef SFMLGAME_LEVEL_H
#define SFMLGAME_LEVEL_H
#include "../Camera/Camera.h"
#include "../GameObjects/NPC.h"
#include "../GameObjects/Player.h"
#include "../Network/Client.h"
#include "../Network/UserData.h"
#include "../Tilemap/Tilemap.h"
#include "../UI/Chatroom.h"
#include "../UI/HealthBar.h"
#include "../UI/PauseMenu.h"
#include "../UI/Scoreboard.h"

class Level : public sf::Drawable
{
 public:
  Level();
  ~Level() = default;
  void init(std::string& player_name, UserData::characterSkin player_skin,int spawnID, unsigned int windowSizeX, unsigned int windowSizeY, const sf::Font& font);
  void update(float dt, Client& client , const sf::Font& font);
  void mouseClicked(sf::Event event ,Client& client,float clickX, float clickY);
  void mouseWheelMoved(sf::Event event);
  int keyPressed(sf::Event event,std::string& username, Client& client, const sf::Font& font);
  void keyReleased(sf::Event event);
  void TextEntered(sf::Event event);

  std::unique_ptr<Tilemap>& getMap();

 private:
  virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

  std::unique_ptr<Tilemap> map_level;

  std::unique_ptr<Player> player;
  std::vector<std::unique_ptr<Player>> otherplayers;
  std::unique_ptr<Chatroom> chatroom;
  std::unique_ptr<Text> username_text;
  std::unique_ptr<PauseMenu> pauseMenu = nullptr;
  std::vector<std::unique_ptr<Bullet>> bullets;
  std::vector<std::unique_ptr<Bullet>> otherBullets;
  std::unique_ptr<HealthBar> healthBar;
  std::unique_ptr<Scoreboard> scoreboard;

  std::unique_ptr<sf::Clock> shot_coolDown;

  //std::unique_ptr<NPC> test;

  int bulletIDsetter= 0;
};

#endif // SFMLGAME_LEVEL_H
