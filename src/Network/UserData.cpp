//
// Created by OscarNg on 2023/10/17.
//

#include "UserData.h"

#include <utility>

UserData::UserData()
{

}

UserData::UserData(std::string username_entered, UserData::characterSkin skin, int playerIDsetter, int kill_num) : UserData()
{
  username = std::move(username_entered);
  skin_chose = skin;
  playerID = playerIDsetter;
  NoOfKills = kill_num;
}

void UserData::setUserName(std::string name)
{
  username = std::move(name);
}

std::string& UserData::getUserName()
{
  return username;
}

void UserData::setCharSkin(UserData::characterSkin charskin)
{
  skin_chose = charskin;
}

UserData::characterSkin UserData::getCharSkin()
{
  return skin_chose;
}

void UserData::setMovingDir(UserData::movingDir moving_direction)
{
  moving_dir = moving_direction;
}

UserData::movingDir UserData::getMovingDir()
{
  return moving_dir;
}

void UserData::setPlayerID(int ID)
{
  playerID = ID;
}

int UserData::getPLayerID()
{
  return playerID;
}

void UserData::setPositionX(float position_x)
{
  positionX = position_x;
}

float UserData::getPostionX()
{
  return positionX;
}

void UserData::setPositionY(float position_y)
{
  positionY = position_y;
}

float UserData::getPostionY()
{
  return positionY;
}

void UserData::sethealth(int hp)
{
  health = hp;
}

int UserData::getHealth()
{
  return health;
}
void UserData::setExitCurrentGame(bool boolean)
{
  exitCurrentGame = boolean;
}

bool UserData::getExitCurrentGame()
{
  return exitCurrentGame;
}

void UserData::setNumOfKills(int killNum)
{
  NoOfKills = killNum;
}

int UserData::getNumOfKills()
{
  return NoOfKills;
}
