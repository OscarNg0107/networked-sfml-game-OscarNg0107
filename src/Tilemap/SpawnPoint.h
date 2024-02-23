//
// Created by OscarNg on 2023/12/5.
//

#ifndef SFMLGAME_SPAWNPOINT_H
#define SFMLGAME_SPAWNPOINT_H
#include <SFML/Graphics.hpp>
#include <memory>
class SpawnPoint
{
 public:
  SpawnPoint();

  SpawnPoint(const int& ID,const float posX, const float posY);

  ~SpawnPoint() = default;

  std::unique_ptr<sf::FloatRect>& GetDetectRange();

  int getID() const;

 float getPositionX() const;
 float getPositionY() const;

 void dRCollisionCheck(sf::Sprite& sprite);

 void setActive(bool boolean);
 bool getActive();

 private:
  int sPID = 0;
  std::unique_ptr<sf::FloatRect> detectRange;
  float positionX;
  float positionY;
  bool active = true;

};

#endif // SFMLGAME_SPAWNPOINT_H
