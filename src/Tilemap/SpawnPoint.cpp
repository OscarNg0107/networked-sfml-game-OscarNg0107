//
// Created by OscarNg on 2023/12/5.
//

#include "SpawnPoint.h"
SpawnPoint::SpawnPoint()
{
  detectRange = std::make_unique<sf::FloatRect>();
}

SpawnPoint::SpawnPoint(const int& ID, const float posX, const float posY) : SpawnPoint()
{
  sPID = ID;
  positionX = posX;
  positionY = posY;

  *detectRange = sf::FloatRect(positionX -200, positionY - 200, 400,400);
}

std::unique_ptr<sf::FloatRect>& SpawnPoint::GetDetectRange()
{
  return detectRange;
}

int SpawnPoint::getID() const
{
  return sPID;
}

float SpawnPoint::getPositionX() const
{
  return positionX;
}

float SpawnPoint::getPositionY() const
{
  return positionY;
}

void SpawnPoint::setActive(bool boolean)
{
  active = boolean;
}

bool SpawnPoint::getActive()
{
  return active;
}
void SpawnPoint::dRCollisionCheck(sf::Sprite& sprite)
{
  if (detectRange->intersects(sprite.getGlobalBounds()))
  {
    active = false;
  }

}
