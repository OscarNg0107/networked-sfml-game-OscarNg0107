//
// Created by st2-ng on 18/10/2023.
//

#ifndef SFMLGAME_TILE_H
#define SFMLGAME_TILE_H

#include <SFML/Graphics.hpp>
#include <memory>

class Tile
{
 public:
  Tile();

  Tile(const int& ID, const sf::Texture& texture);

  ~Tile() = default;

  std::unique_ptr<sf::Sprite>& GetSprite();

  int GetID() const;

 private:
  int tileID = 0;

  std::unique_ptr<sf::Sprite> tileSprite;
};

#endif // SFMLGAME_TILE_H
