//
// Created by OscarNg on 2023/11/9.
//

#ifndef SFMLGAME_CLIENT_H
#define SFMLGAME_CLIENT_H

#include "../GameObjects/Bullet.h"
#include "../GameState/GameState.h"
#include "UserData.h"
#include <SFML/Network.hpp>
#include <atomic>
#include <iostream>
#include <memory>
#include <thread>

class Client
{
 public:
  void connect();
  void input(sf::TcpSocket& iSocket)const;
  void run();
  void receiveMessage();
  void sendPlayerData(std::string& username, UserData::characterSkin skin);
  void sendChatMessage(std::string& username, std::string& string);
  void sendPlayerPosition(float postion_x, float position_y, UserData::movingDir moving_dir);
  void receivePacket();
  void sendPlayerDisconnect();
  void sendPlayerShot(int bulletID,float playerPosX, float playerPosY, sf::Vector2f& shotDirection, float shot_angle);
  void sendEnterGame(std::string& username, UserData::characterSkin skin, bool exitCurrentGame, int kill_num);
  void sendPlayerRespawned();
  void disconnect();

  std::atomic<bool> running = false;
  std::atomic<bool> connected = false;

  int thisPlayerID;
  int otherPlayerID;
  int myHealth;
  int spawnID;
  bool playerDead;
  int myKills= 0;
  std::string username;
  std::string chatText;
  int killnum;
  UserData::characterSkin characterSkin;
  std::vector<std::shared_ptr<UserData>> otherplayersData;
  std::vector<std::unique_ptr<Bullet>> bullets;
  std::vector<std::unique_ptr<Bullet>> otherBullets;

  bool getExistedPlayers    = false;
  bool getExistedPlayers_match = false;
  bool bulletSpawn = false;
  bool healthChange = false;
  bool playerSpawn = false;
  bool myHealthChange = false;
  bool scoreUpdate = false;

  GameState::gameState gameState;
 private:
  std::unique_ptr<sf::TcpSocket> socket;

};

#endif // SFMLGAME_CLIENT_H
