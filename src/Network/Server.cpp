//
// Created by OscarNg on 2023/11/9.
//

#include "Server.h"

void Server::init()
{
  if(listener == nullptr)listener = std::make_unique<sf::TcpListener>();

  if(listener->listen(53000) != sf::Socket::Done)
  {
    std::cout << "fail to connect" << std::endl;
  }

  map_level = std::make_unique<Tilemap>();
  map_level->initMap("Data/Map/Match Map.tmx", "Data/Map/png/streets tiles 2.png");
}

void Server::run()
{
  while (running)
  {
    sf::TcpSocket& cSock =
      connections.emplace_back(std::make_unique<sf::TcpSocket>()).operator*();

    if(listener->accept(cSock) != sf::Socket::Done)
    {
      connections.pop_back();
      return ;
    }
    std::cout << "Client connected @ " << cSock.getRemotePort() << std::endl;
    playerIDsetter +=1;

    workers.emplace_back([&]
                         {
                           listen(cSock);
                         });

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    std::thread gameThread([&]{collionCal(*map_level);});

    gameThread.detach();
  }
}

void Server::listen(sf::TcpSocket& cSocket)
{
  bool continue_receiving = true;
  sf::Packet packet;
  int packetID;

  while(continue_receiving)
  {
    srand((unsigned) time(NULL));

    auto status = cSocket.receive(packet);;
    int portNumber = cSocket.getRemotePort();
    if(status == sf::Socket::Status::Disconnected)
    {
      if(cSocket.getRemotePort() == portNumber)
      {
        std::lock_guard<std::mutex>lock(mutex);
        for(int i =0 ; i< connections.size(); ++i)
        {
          std::cout <<  portNumber << " disconnected"<< std::endl;
          if(connections[i]->getRemotePort() != portNumber)
          {
            continue;
          }
          connections.erase(std::next(connections.begin(), i));
          break ;
        }
      }
      continue_receiving = false;
    }

    packet >> packetID;
    spawnBullet = true;
    if(packetID == 0)
    {
      std::lock_guard<std::mutex>lockLobbyPlayers(lobbyPlayersMutex);
      int skinNum;
      int killNum;
      packet >> username >> skinNum >> killNum;
      characterSkin = static_cast<UserData::characterSkin>(skinNum);
      playersdata.emplace_back(std::make_unique<UserData>(username, characterSkin, playerIDsetter,killNum));


      packet << playerIDsetter;
      sendToClients(packet, portNumber);

      sf::Packet playerID;
      playerID << 1 << playerIDsetter;
      for(auto & player : playersdata)
      {
       if(player->getPLayerID() != playerIDsetter)
       {
         playerID << player->getPLayerID() << player->getUserName() << player->getCharSkin();
       }
      }
      sendToClient(playerID, portNumber);
    }
    else if(packetID == 2)
    {
      sendToClients(packet, portNumber);
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    else if(packetID == 3)
    {
      std::lock_guard<std::mutex>lockMatchPlayers(matchPlayersMutex);
      int playerid;
      float posX;
      float posy;
      packet >> playerid >> posX >> posy;
      for(auto& playerdata : playersdata_inMatch)
      {
        if(playerdata->getPLayerID() == playerid)
        {
          for(auto& player : players)
          {
            if(player->getUserdata().getPLayerID() == playerid)
            {
              player->GetSprite()->setPosition(posX, posy);
            }
          }
        }
      }
      sendToClients(packet, portNumber);
    }
    else if(packetID ==4)
    {
      int disconnectedPLayerID;
      packet >>disconnectedPLayerID;
      std::lock_guard<std::mutex>lockLobbyPlayers(lobbyPlayersMutex);
      for(auto& data : playersdata)
      {
        if(data != nullptr)
        {
          if(data->getPLayerID() == disconnectedPLayerID)
          {
            int dataPos = find(playersdata.begin(), playersdata.end(), data) -
                          playersdata.begin();
            playersdata.erase(playersdata.begin()+ dataPos);
          }
        }
      }
      continue_receiving = false;
    }

    else if(packetID == 5)
    {
      int playerID;
      int bulletID;
      float shotDirX;
      float shotDirY;
      float shotPosX;
      float shotPosY;
      float shotAngle;
      packet >> playerID >> bulletID >>  shotDirX >> shotDirY >> shotPosX >> shotPosY >> shotAngle;
      sf::Vector2f shotDir = sf::Vector2f(shotDirX, shotDirY);

      if(spawnBullet)
      {
        bullets.emplace_back(std::make_shared<Bullet>(playerID,bulletID, shotPosX, shotPosY, shotDir,shotAngle));
        spawnBullet = false;
      }
      sendToClients(packet, portNumber);
    }

    else if(packetID == 8)
    {
      std::lock_guard<std::mutex>lockPlayers(playersMutex);
      int skinNum;
      int playerID;
      bool playerExitCurrentGame;
      int kill_num;
      packet >> username >> skinNum >> playerID >> playerExitCurrentGame >> kill_num;

      characterSkin = static_cast<UserData::characterSkin>(skinNum);

      std::lock_guard<std::mutex>lockMatchPlayers(matchPlayersMutex);
      playersdata_inMatch.emplace_back(std::make_unique<UserData>(username, characterSkin, playerID, kill_num));

      std::lock_guard<std::mutex>lockLobbyPlayers(lobbyPlayersMutex);

      for(auto& playerInLobby : playersdata)
      {
        if(playerInLobby != nullptr)
        {
          if(playerInLobby->getPLayerID() == playerID)
          {
            int pos = find(playersdata.begin(), playersdata.end(), playerInLobby) - playersdata.begin();
            playersdata.erase(playersdata.begin() + pos);
          }
        }
      }
      sendToClients(packet, portNumber);

      sf::Packet newPacket;
      newPacket << 9;

      randomSpID = getSpawnID();

      newPacket << randomSpID;

      for(auto & player : playersdata_inMatch)
      {
        if(player->getPLayerID() != playerID)
        {
          newPacket << player->getPLayerID() << player->getUserName() << player->getCharSkin() << player->getNumOfKills();
        }
      }
      sendToClient(newPacket, portNumber);

      players.emplace_back(std::make_unique<Player>(playerID, username, characterSkin));
      players.back()->setSpawned(true);

      std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    else if(packetID == 11)
    {
      //std::lock_guard<std::mutex>lockPlayers(playersMutex);
      std::cout << "player respawn" << std::endl;
      int playerID;
      packet >> playerID;
      for(auto& player : players)
      {
        if(player->getUserdata().getPLayerID() == playerID)
        {
          player->setHealth(3);
        }
      }
    }
  }
  cSocket.disconnect();
}

void Server::collionCal(Tilemap& tilemap)
{
  sf::Clock clock;
  while(running)
  {
    sf::Time time = clock.restart();
    float dt = time.asSeconds();

    std::lock_guard<std::mutex>lockBullets(bulletMutex);
    for(auto& bullet : bullets)
    {
      if (bullet != nullptr)
      {
        if (!bullet->getHitBool())
        {
          bullet->update(dt, tilemap.getTilemap());
          int collisionID = bullet->CollisionCheck(tilemap.getTilemap(), players);
          if (collisionID == 1)
          {
            sf::Packet packet;
            packet << 7 << bullet->getOwnerID() << bullet->getBulletID();
            sendAllClients(packet);

            int pos =
              find(bullets.begin(), bullets.end(), bullet) - bullets.begin();
            bullets.erase(bullets.begin() + pos);
          }

          else if(collisionID == 2)
          {
            int colliedPlayerID = bullet->colliedPlayerID;
            int colliedPlayerHp = bullet->colliedPlayerHp;
            sf::Packet packet;
            packet << 7 << bullet->getOwnerID() << bullet->getBulletID();
            sendAllClients(packet);

            int pos = find(bullets.begin(), bullets.end(), bullet) -
                      bullets.begin();
            bullets.erase(bullets.begin() + pos);

            sf::Packet packet_health;
            packet_health << 10 << colliedPlayerID << colliedPlayerHp;
            if(colliedPlayerHp <= 0)
            {
              bool playerDead  = true;
              randomRspID = getSpawnID();
              std::this_thread::sleep_for(std::chrono::milliseconds(100));
              packet_health << playerDead;
              packet_health << randomRspID;

              for(auto& userdata : playersdata_inMatch)
              {
                if(userdata->getPLayerID() == bullet->getOwnerID())
                {
                  userdata->setNumOfKills(userdata->getNumOfKills() + 1);
                  sf::Packet packet_score;
                  packet_score << 12;
                  packet_score << bullet->getOwnerID();
                  packet_score << userdata->getNumOfKills();
                  sendAllClients(packet_score);
                  userdata->sethealth(3);
                }
              }
            }
            std::cout << "Player" << colliedPlayerID << ": " << colliedPlayerHp<< std::endl;


            sendAllClients(packet_health);
          }
        }
      }
    }


    for (auto& defaultSp : map_level->getSpawnPoints()[0])
    {
      std::lock_guard<std::mutex>lockPlayers(playersMutex);
      bool active = true;
      for (auto& player : players)
      {
        if(player!= nullptr)
        {
          if(player->getSpawned())
          {
            if (player->GetSprite()->getGlobalBounds().intersects(
                  *defaultSp->GetDetectRange()))
            {
              active = false;
              break ;
            }
          }
        }
      }
      defaultSp->setActive(active);
    }
  }
}

void Server::sendAllClients(sf::Packet packet)
{
  std::lock_guard<std::mutex>lock(mutex);

  for(auto & connection : connections)
  {
    connection->send(packet);
  }
}

void Server::sendToClients(sf::Packet packet, int portNum)
{
  std::lock_guard<std::mutex>lock(mutex);

  for(auto & connection : connections)
  {
    if(connection->getRemotePort() != portNum)
    {
      connection->send(packet);

    }
  }
}

void Server::sendToClient(sf::Packet packet, int portNum)
{
  std::lock_guard<std::mutex>lock(mutex);

  for(auto & connection : connections)
  {
    if(connection->getRemotePort() == portNum)
    {
      connection->send(packet);
    }
  }
}

int Server::getSpawnID()
{
  int ID;
  while (true)
  {
    ID = rand() % map_level->getSpawnPoints()[0].size();

    if(map_level->getSpawnPoints()[0][ID]->getActive())
    {
      std::cout << "getID: " << ID << std::endl;
      return ID;
    }
  }
}
