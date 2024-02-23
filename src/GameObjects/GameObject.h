//
// Created by OscarNg on 2023/10/20.
//

#ifndef SFMLGAME_GAMEOBJECT_H
#define SFMLGAME_GAMEOBJECT_H
#include <SFML/Graphics.hpp>

class GameObject
{
 public:
  GameObject();
  ~GameObject() =default;
  void initSprite(const sf::Texture& texture);
  std::unique_ptr<sf::Sprite>& GetSprite();

 private:
  std::unique_ptr<sf::Sprite> up_objectSprite = nullptr;

};

#endif // SFMLGAME_GAMEOBJECT_H
