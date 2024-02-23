//
// Created by OscarNg on 2023/10/21.
//
#include "GameObject.h"
#ifndef SFMLGAME_CHARACTER_H
#define SFMLGAME_CHARACTER_H
#include <math.h>

class Character : public GameObject
{
 public:
  Character();
  ~Character()= default;
  void hitbox();
  std::unique_ptr<sf::FloatRect>& getTopHitbox();
  std::unique_ptr<sf::FloatRect>& getBottomHitbox();
  std::unique_ptr<sf::FloatRect>& getLeftHitbox();
  std::unique_ptr<sf::FloatRect>& getRightHitbox();
  void setHealth(int character_health);
  int getHealth();
  void setIsDead(bool boolean);
  bool GetIsDead();

  sf::Vector2f normalizeVector(float x, float y);
  void setMovingDir(float x, float y);
  sf::Vector2f getMovingDir();
 private:
  int health;
  bool isDead;
  sf::Vector2f movingDirection = sf::Vector2f(0,0);
  float speed = 2.0f;

  std::unique_ptr<sf::FloatRect> hitbox_top;
  std::unique_ptr<sf::FloatRect> hitbox_bottom;
  std::unique_ptr<sf::FloatRect> hitbox_left;
  std::unique_ptr<sf::FloatRect> hitbox_right;

};

#endif // SFMLGAME_CHARACTER_H
