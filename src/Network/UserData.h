//
// Created by OscarNg on 2023/10/17.
//
#include <string>
#ifndef SFMLGAME_USERDATA_H
#define SFMLGAME_USERDATA_H


class UserData
{
 public:

  enum characterSkin{
    DAVID,
    LUCY,
    REBECCA
  };

  enum movingDir
  {
    NONE,
    UP,
    DOWN,
    LEFT,
    RIGHT
  };

  UserData();
  UserData(std::string username_entered, UserData::characterSkin skin, int playerIDsetter, int killNum);
  ~UserData() = default;

  void setUserName(std::string name);
  std::string& getUserName();

  void setCharSkin(UserData::characterSkin charskin);
  characterSkin getCharSkin();

  void setMovingDir(UserData::movingDir moving_direction);
  movingDir getMovingDir();

  void setPlayerID(int ID);
  int getPLayerID();

  void setPositionX(float position_x);
  float getPostionX();

  void setPositionY(float position_x);
  float getPostionY();

  void sethealth(int hp);
  int getHealth();

  void setExitCurrentGame(bool boolean);
  bool getExitCurrentGame();

  void setNumOfKills(int killNum);
  int getNumOfKills();


 private:
  std::string username;
  characterSkin skin_chose;
  movingDir moving_dir;

  int playerID;

  float positionX;
  float positionY;

  int health = 3;

  int NoOfKills = 0;

  bool exitCurrentGame = false;

};

#endif // SFMLGAME_USERDATA_H
