//
// Created by OscarNg on 2023/10/22.
//

#include "Tilemap.h"
#include "tmxlite/Map.hpp"
#include <cmath>
#include <iostream>

void Tilemap::initMap(const std::string& tmx_file, const std::string& spritesheet)
{
  tmx::Map map;

  if(!tileMap->loadFromFile(spritesheet))
  {
    std::cout<< "FAILED TO LOAD SPRITESHEET"<< std::endl;
  }

  if(!map.load(tmx_file))
  {
    std::cout << "FAILED TO LOAD MAP DATA" << std::endl;
  }
  map_size_X = map.getTileCount().x * map.getTileSize().x;
  map_size_Y = map.getTileCount().y * map.getTileSize().y;

  const unsigned int MAP_COLUMNS = map.getTileCount().x;
  const unsigned int MAP_ROWS = map.getTileCount().y;

  auto& tile_size = map.getTileSize();


  TILE_MAP.reserve(map.getLayers().size());
  spawnPoints.reserve(map.getLayers().size());

  int layerID = 0;
  for(const auto& layer : map.getLayers())
  {

    TILE_MAP.emplace_back(std::vector<std::unique_ptr<Tile>>());

    if(layer->getType() == tmx::Layer::Type::Tile)
    {
      const auto& tiles = layer->getLayerAs<tmx::TileLayer>().getTiles();
      TILE_MAP.back().reserve(tiles.size());

      for (const auto& tile : tiles)
      {
        SetTileWithID(MAP_COLUMNS, tile_size, tile, layerID);
      }
    }
    else if(layer->getType() == tmx::Layer::Type::Object)
    {
      spawnPoints.emplace_back(std::vector<std::unique_ptr<SpawnPoint>>());

      const auto& objectLayer = layer->getLayerAs<tmx::ObjectGroup>();
      const auto& objects = objectLayer.getObjects();
      spawnPoints.back().reserve(objects.size());
      for(auto& i : objects)
      {
        spawnPoints.back().emplace_back(std::make_unique<SpawnPoint>(i.getUID(), i.getPosition().x, i.getPosition().y));
      }
    }
    layerID += 1;
  }
}

void Tilemap::SetTileWithID(const unsigned int MAP_COLUMNS, const tmx::Vector2u& tile_size, const tmx::TileLayer::Tile& tile, int layerID)
{
  auto& current = *TILE_MAP.back().emplace_back(
    std::make_unique<Tile>(tile.ID, *tileMap));

  current.GetSprite()->setPosition(((TILE_MAP.back().size() -1) % MAP_COLUMNS)* tile_size.x,
                                   ((TILE_MAP.back().size() - 1) / MAP_COLUMNS) * tile_size.y);

  if(current.GetID() == 0)
  {
    current.GetSprite()->setTextureRect(
      sf::IntRect(0,0,32,32));
    emptyTiles[layerID].push_back(*current.GetSprite());
  }

  else
  {
    current.GetSprite()->setTextureRect(
      sf::IntRect((current.GetID()-1) % (tileMap->getSize().x /32) * tile_size.x,
                  ((std::floor((current.GetID() -1) /(tileMap->getSize().x /32))) * tile_size.y),
                  tile_size.x, tile_size.y));
  }
}

std::vector<std::vector<std::unique_ptr<Tile>>>& Tilemap::getTilemap()
{
  return TILE_MAP;
}

std::vector<std::vector<std::unique_ptr<SpawnPoint>>>& Tilemap::getSpawnPoints()
{
    return spawnPoints;
}

std::vector<sf::Sprite>& Tilemap::getEmptyTiles(int layerID)
{
  return emptyTiles[layerID];
}

float Tilemap::getMapSizeX()
{
  return map_size_X;
}

float Tilemap::getMapSizeY()
{
  return map_size_Y;
}

void Tilemap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.clear(sf::Color::Black);
  for(const auto& layer : TILE_MAP)
  {
    for(const auto& tile : layer)
    {
      if(tile->GetID() != 0)
      {
        target.draw(*tile->GetSprite());
      }
    }
  }
}
