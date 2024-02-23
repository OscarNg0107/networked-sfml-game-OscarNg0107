//
// Created by OscarNg on 2023/10/24.
//

#include "Camera.h"

Camera::Camera()
{
  p_camera = std::make_unique<sf::View>();
}
void Camera::initCamera(unsigned int windowSizeX, unsigned int windowSizeY, sf::Sprite& target)
{
  p_camera->setSize(1920, 1080);
  p_camera->setCenter(target.getPosition().x + target.getGlobalBounds().width/2,
                      target.getPosition().y + target.getGlobalBounds().height/2);
}
void Camera::MoveCamera(float dt, sf::Sprite& target,sf::Vector2f movingDir, std::vector<std::vector<std::unique_ptr<Tile>>>& map)
{
  if ((target.getPosition().x + target.getGlobalBounds().width/2 >= getCamera()->getCenter().x && movingDir.x > 0)||
      (target.getPosition().x + target.getGlobalBounds().width/2 <= getCamera()->getCenter().x && movingDir.x <0) ||
      (target.getPosition().y + target.getGlobalBounds().height/2 >= getCamera()->getCenter().y && movingDir.y >0) ||
      (target.getPosition().y + target.getGlobalBounds().height/2 <= getCamera()->getCenter().y && movingDir.y <0))
  {
    p_camera->move(movingDir.x , movingDir.y);
  }

  if(p_camera->getCenter().y - p_camera->getSize().y/2 <= map[0][0]->GetSprite()->getPosition().y)
  {
    p_camera->setCenter(p_camera->getCenter().x, map[0][0]->GetSprite()->getPosition().y + p_camera->getSize().y/2);
  }
  if(p_camera->getCenter().y + p_camera->getSize().y/2 >= map[0][map[0].size()-2]->GetSprite()->getPosition().y  + map[0][map[0].size()-2]->GetSprite()->getGlobalBounds().height)
  {
    p_camera->setCenter(p_camera->getCenter().x, map[0][map[0].size()-2]->GetSprite()->getPosition().y + map[0][map[0].size()-2]->GetSprite()->getGlobalBounds().height- p_camera->getSize().y/2);
  }
  if(p_camera->getCenter().x - p_camera->getSize().x/2 <= map[0][0]->GetSprite()->getPosition().x)
  {
    p_camera->setCenter(map[0][0]->GetSprite()->getPosition().x + p_camera->getSize().x/2, p_camera->getCenter().y);
  };
  if(p_camera->getCenter().x + p_camera->getSize().x/2 >= map[0][map[0].size()-2]->GetSprite()->getPosition().x + map[0][map[0].size()-2]->GetSprite()->getGlobalBounds().width)
  {
    p_camera->setCenter(map[0][map[0].size()-2]->GetSprite()->getPosition().x + map[0][map[0].size()-2]->GetSprite()->getGlobalBounds().width - p_camera->getSize().x/2 ,p_camera->getCenter().y);
  }
}

std::unique_ptr<sf::View>& Camera::getCamera()
{
  return p_camera;
}

