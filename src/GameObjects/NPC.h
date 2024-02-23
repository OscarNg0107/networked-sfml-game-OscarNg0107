//
// Created by OscarNg on 2023/10/28.
//

#ifndef SFMLGAME_NPC_H
#define SFMLGAME_NPC_H
#include "Character.h"

class NPC : public Character
{
 public:

  void raycasting(unsigned int windowSizeX, unsigned int windowSizeY);

  sf::Texture test_texture;

  sf::Vector2f lookingDir = sf::Vector2f( 0,1);

  sf::Vector2f plane = sf::Vector2f (0, 0.66);

  double time = 0;

  double oldTime = 0;

 private:


};

#endif // SFMLGAME_NPC_H
