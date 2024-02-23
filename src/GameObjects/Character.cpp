//
// Created by OscarNg on 2023/10/21.
//

#include "Character.h"

Character::Character()
{
  hitbox_top            = std::make_unique<sf::FloatRect>();
  hitbox_bottom         = std::make_unique<sf::FloatRect>();
  hitbox_left           = std::make_unique<sf::FloatRect>();
  hitbox_right          = std::make_unique<sf::FloatRect>();
}
void Character::hitbox()
{
  *hitbox_top = sf::FloatRect(GetSprite()->getPosition().x + GetSprite()->getGlobalBounds().width /4,
                                   GetSprite()->getPosition().y,
                                   GetSprite()->getGlobalBounds().width/2,
                                   GetSprite()->getGlobalBounds().height/4);

  *hitbox_bottom = sf::FloatRect (GetSprite()->getPosition().x + GetSprite()->getGlobalBounds().width /4,
                                      GetSprite()->getPosition().y + GetSprite()->getGlobalBounds().width - hitbox_bottom->height,
                                      GetSprite()->getGlobalBounds().width/2,
                                      GetSprite()->getGlobalBounds().height/4);

  *hitbox_left = sf::FloatRect (GetSprite()->getPosition().x,
                                    GetSprite()->getPosition().y + GetSprite()->getGlobalBounds().height /4,
                                    GetSprite()->getGlobalBounds().width/4,
                                    GetSprite()->getGlobalBounds().height/2);

  *hitbox_right = sf::FloatRect (GetSprite()->getPosition().x + GetSprite()->getGlobalBounds().width - hitbox_right->width,
                                     GetSprite()->getPosition().y + GetSprite()->getGlobalBounds().height /4,
                                     GetSprite()->getGlobalBounds().width/4,
                                     GetSprite()->getGlobalBounds().height/2);
}

std::unique_ptr<sf::FloatRect>& Character::getTopHitbox()
{
    return hitbox_top;
}

std::unique_ptr<sf::FloatRect>& Character::getBottomHitbox()
{
    return hitbox_bottom;
}

std::unique_ptr<sf::FloatRect>& Character::getLeftHitbox()
{
    return hitbox_left;
}

std::unique_ptr<sf::FloatRect>& Character::getRightHitbox()
{
  return hitbox_right;
}

void Character::setIsDead(bool boolean)
{
  isDead = boolean;
}
bool Character::GetIsDead()
{
  return isDead;
}

void Character::setHealth(int character_health)
{
  health = character_health;
}

int Character::getHealth()
{
  return health;
}

sf::Vector2f Character::normalizeVector(float x, float y)
{
  float magnitude = sqrt((x * x) + (y * y));
  if(magnitude != 0)
    return sf::Vector2f(x /magnitude, y/magnitude);
  else
    return sf::Vector2f(x,y);
}

void Character::setMovingDir(float x, float y)
{
  movingDirection = normalizeVector(x,y) * speed;

}

sf::Vector2f Character::getMovingDir()
{
  return movingDirection;
}
