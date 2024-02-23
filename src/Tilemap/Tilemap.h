//
// Created by OscarNg on 2023/10/22.
//

#ifndef SFMLGAME_TILEMAP_H
#define SFMLGAME_TILEMAP_H
#include "SpawnPoint.h"
#include "Tile.h"
#include "tmxlite/Map.hpp"
#include "tmxlite/TileLayer.hpp"
#include <SFML/Graphics.hpp>

class Tilemap : public sf::Drawable
{
 public:
  void initMap(const std::string& tmx_file, const std::string& spritesheet);
  void SetTileWithID(const unsigned int MAP_COLUMNS, const tmx::Vector2u& tile_size,
                     const tmx::TileLayer::Tile& tile, int layerID);
  std::vector<std::vector<std::unique_ptr<Tile>>>& getTilemap();
  std::vector<std::vector<std::unique_ptr<SpawnPoint>>>& getSpawnPoints();


  std::vector<sf::Sprite>& getEmptyTiles(int layerID);

  float getMapSizeX();
  float getMapSizeY();


 private:
  std::unique_ptr<sf::Texture> tileMap = std::make_unique<sf::Texture>();

  std::vector<std::vector<std::unique_ptr<Tile>>> TILE_MAP;

  std::vector<std::vector<std::unique_ptr<SpawnPoint>>> spawnPoints;

  std::vector<sf::Sprite> emptyTiles[3];

  virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const ;
  float map_size_X;
  float map_size_Y;
};

#endif // SFMLGAME_TILEMAP_H
