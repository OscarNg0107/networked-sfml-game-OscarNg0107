//
// Created by OscarNg on 2023/11/9.
//

#ifndef SFMLGAME_SERVER_H
#define SFMLGAME_SERVER_H

#include <SFML/Network.hpp>
#include <thread>
#include <list>
#include <iostream>
#include <mutex>
#include <memory>
#include <random>

#include "../GameObjects/Bullet.h"
#include "../GameObjects/Player.h"
#include "UserData.h"

class Server
{
 public:
  void init();
  void run();
  void listen(sf::TcpSocket& cSocket);
  void collionCal(Tilemap& tilemap);
  void sendAllClients(sf::Packet packet);
  int getSpawnID();
  void sendToClients(sf::Packet packet, int portNum);
  void sendToClient(sf::Packet packet, int portNum);

 private:
  std::vector<std::thread> workers;
  std::vector<std::unique_ptr<sf::TcpSocket>> connections;

  std::unique_ptr<sf::TcpListener> listener;
  std::unique_ptr<sf::TcpSocket> socket;



  bool running = true;
  std::mutex mutex;

  std::mutex bulletMutex;

  std::string username;
  UserData::characterSkin characterSkin;
  int playerIDsetter = 0;

  std::string chatText;

  std::vector<std::unique_ptr<UserData>> playersdata;
  std::vector<std::unique_ptr<UserData>> playersdata_inMatch;

  std::mutex lobbyPlayersMutex;
  std::mutex matchPlayersMutex;

  std::unique_ptr<Tilemap> map_level;
  std::vector<std::unique_ptr<Player>> players;
  std::vector<std::shared_ptr<Bullet>> bullets;

  std::mutex playersMutex;

  bool spawnBullet = false;

  int randomSpID;
  int randomRspID;
};

#endif // SFMLGAME_SERVER_H
