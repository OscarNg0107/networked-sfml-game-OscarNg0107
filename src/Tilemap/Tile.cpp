//
// Created by st2-ng on 18/10/2023.
//

#include "Tile.h"


Tile::Tile()
{
  tileSprite = std::make_unique<sf::Sprite>();
}

Tile::Tile(const int& ID, const sf::Texture& texture) : Tile()
{
  tileID = ID;
  tileSprite->setTexture(texture);
}

std::unique_ptr<sf::Sprite>& Tile::GetSprite()
{
  return tileSprite;
}

int Tile::GetID() const
{
  return tileID;
}