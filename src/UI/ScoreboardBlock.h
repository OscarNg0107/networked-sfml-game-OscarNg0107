//
// Created by OscarNg on 2023/12/5.
//

#ifndef SFMLGAME_SCOREBOARDBLOCK_H
#define SFMLGAME_SCOREBOARDBLOCK_H
#include "../GameObjects/GameObject.h"
#include "../Network/UserData.h"
#include "Text.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <sstream>

class ScoreboardBlock : public sf::Drawable
{
 public:
  ScoreboardBlock();
  ScoreboardBlock(std::string& name,const sf::Font& font,UserData::characterSkin skin, int ID, int kill_num);
  ~ScoreboardBlock() =default;

  void init(std::string& name,const sf::Font& font,UserData::characterSkin skin, int ID, int kill_num);

  void setPosition(float posX, float posY);
  void setKillNum(int kill_num);

  const sf::Vector2f& getBlockSize();

  int getPlayerID();

  int getKillNum();

 private:
  virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
  std::unique_ptr<sf::RectangleShape> panel_base;
  std::unique_ptr<GameObject> charIcon;
  std::unique_ptr<sf::Texture> charIcon_texture;
  std::unique_ptr<Text> text_username;
  std::unique_ptr<Text> text_killNum;

  int playerID;
  int killNum;
};

#endif // SFMLGAME_SCOREBOARDBLOCK_H
