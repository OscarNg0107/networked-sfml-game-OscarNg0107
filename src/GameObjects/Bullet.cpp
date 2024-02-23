//
// Created by OscarNg on 2023/10/29.
//

#include "Bullet.h"
#include <iostream>
#include <cmath>
Bullet::Bullet()
{
  bullet_texture = std::make_unique<sf::Texture>();
  bullet_texture->loadFromFile("Data/Images/weapon/bullet shot.png") ;
  initSprite(*bullet_texture);
}

Bullet ::Bullet(int bullet_id,float playerPosX, float playerPosY, float clickX, float clickY) : Bullet()
{
  bulletID = bullet_id;
  GetSprite()->setPosition(playerPosX, playerPosY);
  float magnitude = sqrt((pow((clickX - playerPosX),2) + pow((clickY - playerPosY),2)));
  movingDir = sf::Vector2f ((clickX - playerPosX) / magnitude, (clickY - playerPosY) /magnitude);
  angle = std::atan2(clickY - GetSprite()->getPosition().y, clickX - GetSprite()->getPosition().x);
  angle = angle * (180/ M_PI);
  GetSprite()->setRotation(angle);
}

Bullet::Bullet(int owner_id,int bullet_id,float playerPosX, float playerPosY, sf::Vector2f& shotDirection, float shot_angle) : Bullet()
{
  bulletID = bullet_id;
  ownerID = owner_id;
  GetSprite()->setPosition(playerPosX, playerPosY);
  movingDir = shotDirection;
  angle = shot_angle;
  GetSprite()->setRotation(angle);
}

void Bullet::update(float dt , std::vector<std::vector<std::unique_ptr<Tile>>>& map)
{
  GetSprite()->move(movingDir * bullet_speed * dt);
}

int Bullet::CollisionCheck(std::vector<std::vector<std::unique_ptr<Tile>>>& map, std::vector<std::unique_ptr<Player>>& players)
{
  for(auto & i : map[1])
  {
    if(GetSprite()->getGlobalBounds().intersects(i->GetSprite()->getGlobalBounds()))
    {
      if(i->GetID() != 0)
      {
        std::cout << i->GetID() << std::endl;
        std::cout << i->GetSprite()->getPosition().x <<" " << i->GetSprite()->getPosition().y << std::endl;
        hit = true;
        return 1;
      }
    }
  }
  for(auto & i : map[0])
  {
    if(GetSprite()->getPosition().x < map[0].front()->GetSprite()->getPosition().x ||
        GetSprite()->getPosition().x + GetSprite()->getGlobalBounds().width > map[0].back()->GetSprite()->getPosition().x + map[0].back()->GetSprite()->getGlobalBounds().width||
        GetSprite()->getPosition().y < map[0].front()->GetSprite()->getPosition().y ||
        GetSprite()->getPosition().y + GetSprite()->getGlobalBounds().height > map[0].back()->GetSprite()->getPosition().y + map[0].back()->GetSprite()->getGlobalBounds().height)
    {
      hit = true;
      return 1;
    }
  }
  for(auto& player : players)
  {
    if(player != nullptr)
    {
      if(ownerID != player->getUserdata().getPLayerID())
      {
        if(GetSprite()->getGlobalBounds().intersects(player->GetSprite()->getGlobalBounds()))
        {
          player->setHealth(player->getHealth() - 1);
          colliedPlayerID = player->getUserdata().getPLayerID();
          colliedPlayerHp = player->getHealth();
          hit = true;
          return 2;
        }
      }
    }
  }

  return 0;
}

void Bullet::setHitBool(bool boolean)
{
  hit = boolean;
}

bool Bullet::getHitBool()
{
  return hit;
}

sf::Vector2f& Bullet::getMovingDir()
{
  return movingDir;
}

float Bullet::getAngle()
{
  return angle;
}

void Bullet::setBulletID(int ID)
{
  bulletID = ID;
}

int Bullet::getBulletID()
{
  return bulletID;
}

int Bullet::getOwnerID()
{
  return ownerID;
}