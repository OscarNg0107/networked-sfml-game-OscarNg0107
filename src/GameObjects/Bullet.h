//
// Created by OscarNg on 2023/10/29.
//

#ifndef SFMLGAME_BULLET_H
#define SFMLGAME_BULLET_H
#include "../Camera/Camera.h"
#include "../Tilemap/Tilemap.h"
#include "GameObject.h"
#include "Player.h"

class Bullet : public GameObject
{
 public:
  Bullet();
  Bullet(int bullet_id,float playerPosX , float playerPosY, float clickX, float clickY);
  Bullet(int owner_id, int bullet_id,float playerPosX , float playerPosY,sf::Vector2f& shotDirection, float shot_angle);
  ~Bullet() = default;

  void update(float dt ,std::vector<std::vector<std::unique_ptr<Tile>>>& map);
  int CollisionCheck(std::vector<std::vector<std::unique_ptr<Tile>>>& map , std::vector<std::unique_ptr<Player>>& players);
  void setHitBool(bool boolean);
  bool getHitBool();
  sf::Vector2f& getMovingDir();

  float getAngle();

  void setBulletID(int ID);
  int getBulletID();

  int getOwnerID();
  int colliedPlayerID;
  int colliedPlayerHp;
 private:
  std::unique_ptr<sf::Texture> bullet_texture;

  float bullet_speed = 1000.0f;
  sf::Vector2f movingDir;
  bool hit = false;

  int bulletID;
  int ownerID;

  float angle;


};

#endif // SFMLGAME_BULLET_H
