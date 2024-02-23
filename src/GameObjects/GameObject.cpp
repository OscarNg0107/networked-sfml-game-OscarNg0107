//
// Created by OscarNg on 2023/10/20.
//

#include "GameObject.h"
#include <iostream>

GameObject::GameObject()
{
  up_objectSprite = std::make_unique<sf::Sprite>();
}

void GameObject::initSprite(const sf::Texture& texture)
{
  up_objectSprite->setTexture(texture);
}


std::unique_ptr<sf::Sprite>& GameObject::GetSprite()
{
  return up_objectSprite;
}

