//
// Created by OscarNg on 2023/10/28.
//

#include "NPC.h"

void NPC::raycasting(unsigned int windowSizeX, unsigned int windowSizeY)
{
  for(int i =0 ; i < windowSizeX ; ++i)
  {
    double cameraX = 2 * i / double(windowSizeX) - 1;
    sf::Vector2f rayDir = sf::Vector2f (lookingDir.x + plane.x * cameraX, lookingDir.y + plane.y * cameraX);
  }
}