//
// Created by OscarNg on 2023/10/24.
//

#ifndef SFMLGAME_CAMERA_H
#define SFMLGAME_CAMERA_H
#include "../Tilemap/Tile.h"
#include <SFML/Graphics.hpp>

class Camera
{
 public:
  Camera();
  ~Camera() = default;
  void initCamera(unsigned int windowSizeX, unsigned int windowSizeY, sf::Sprite& target);
  void MoveCamera(float dt, sf::Sprite& target, sf::Vector2f movingDir , std::vector<std::vector<std::unique_ptr<Tile>>>& map);

  std::unique_ptr<sf::View>& getCamera();


 private:
  std::unique_ptr<sf::View> p_camera;

  float speed = 150;
};

#endif // SFMLGAME_CAMERA_H
