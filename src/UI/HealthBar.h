//
// Created by OscarNg on 2023/12/4.
//

#ifndef SFMLGAME_HEALTHBAR_H
#define SFMLGAME_HEALTHBAR_H

#include "../Camera/Camera.h"
#include "../GameObjects/GameObject.h"
#include "../Network/UserData.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class HealthBar: public sf::Drawable
{
 public:
  HealthBar();
  ~HealthBar() = default;

  void init(int fullHealth, UserData::characterSkin player_skin, float scale);
  void setPostion(Camera& camera);
  void resetHealthBar(float scale);
  void healthchanged(int newHealth);

 private:
  virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

  std::unique_ptr<GameObject> charIconBox;
  std::unique_ptr<sf::Texture> charIconBox_texture;
  std::unique_ptr<GameObject> charIcon;
  std::unique_ptr<sf::Texture> charIcon_texture;
  std::unique_ptr<GameObject> hpBox;
  std::unique_ptr<sf::Texture> hpBox_texture;
  std::unique_ptr<GameObject> healthBar;
  std::unique_ptr<sf::Texture> healthBar_texture;


  int fullHp;
};

#endif // SFMLGAME_HEALTHBAR_H
