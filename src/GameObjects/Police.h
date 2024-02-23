//
// Created by OscarNg on 2023/10/28.
//

#ifndef SFMLGAME_POLICE_H
#define SFMLGAME_POLICE_H
#include "NPC.h"
class Police : public NPC
{
 public:
  enum State
  {
    IDLE,
    SEARCH,
    CHASE,
    ATTACK,
    FINDING,
    DEATH
  };

 private:
  State behavior = IDLE;
};

#endif // SFMLGAME_POLICE_H
