//
// Created by OscarNg on 2023/12/5.
//

#ifndef SFMLGAME_SCOREBOARD_H
#define SFMLGAME_SCOREBOARD_H
#include "../Camera/Camera.h"
#include "ScoreboardBlock.h"
#include <iostream>

class Scoreboard : public sf::Drawable
{
 public:
  Scoreboard();
  ~Scoreboard() =default;

  void init(const sf::Font& font, Camera& camera);
  void addPlayer(std::string& name,const sf::Font& font, UserData::characterSkin skin, int ID, int kill_num);
  void update(Camera& camera);
  void keyPressed(sf::Event event);
  void keyReleased(sf::Event event);
  void bubbleSort(std::vector<std::unique_ptr<ScoreboardBlock>>& players);

  std::vector<std::unique_ptr<ScoreboardBlock>>& getPlayerList();
 private:

  virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const ;
  std::unique_ptr<sf::RectangleShape> panel_base;
  std::unique_ptr<Text> title_player;

  std::unique_ptr<GameObject> killIcon;
  std::unique_ptr<sf::Texture> killIcon_texture;
  std::vector<std::unique_ptr<ScoreboardBlock>> playerlist;

  bool isVisible;
};

#endif // SFMLGAME_SCOREBOARD_H
