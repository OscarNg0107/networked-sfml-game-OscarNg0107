//
// Created by OscarNg on 2023/11/9.
//

#include "Client.h"

void Client::connect()
{
  if(socket == nullptr)socket = std::make_unique<sf::TcpSocket>();

  if(socket->connect("127.0.0.1",53000) == sf::Socket::Status::Done)
  {
    std::cout << "You're Connected" << std::endl;
    connected = true;
    run();
  }
  else
  {
    std::cout << "failed to connect";
  }
}

void Client::run()
{
  running = true;

  std::thread input_thread([&]{
                             input(*socket);
                           });
  input_thread.detach();

  std::thread receiveMessage_thread([&]{
                                      receiveMessage();
                                    });
  receiveMessage_thread.detach();

  std::thread receivePacket_thread([&]{
                                     receivePacket();
                                   });
  receivePacket_thread.detach();
}

void Client::input(sf::TcpSocket& iSocket) const
{
  while (running)
  {
    std::string str;
    std::getline(std::cin, str);
    std::cin.clear();

    if(connected)
    {
      //iSocket.sendToClients(reinterpret_cast<char*>(str.data()), str.length());
    }
  }
}

void Client::receiveMessage()
{
  while (running && connected)
  {
    char static_buffer[1028];
    while (connected)
    {
      /*std::size_t received;
      auto status = socket->receive(static_buffer, 1028, received);

      if(status == sf::Socket::Status::Disconnected)
      {
        connected = false;
        std::cout << "clean disconnection" << std::endl;
        socket->disconnect();
        break ;
      }
      else
      {
        if(received < 1028)
        {
          static_buffer[received] = '\0';
        }
        std::cout << static_buffer << '\n';
      }*/
    }
  }
}

void Client::sendPlayerData(std::string& username, UserData::characterSkin skin)
{
  sf::Packet packet;
  packet << 0;
  packet << username;
  packet << static_cast<int>(skin);
  packet << 0;
  if(connected)
  {
    socket->send(packet);
  }
}

void Client::sendChatMessage(std::string& username, std::string& string)
{
    sf::Packet packet;
    std::string combinedString ="<"+  username + ">" + string;
    packet << 2;
    packet << static_cast<int>(gameState);
    packet << combinedString;

    if(connected)
    {
      socket->send(packet);
    }
}

void Client::sendPlayerPosition(float postion_x, float position_y, UserData::movingDir moving_dir)
{
  sf::Packet packet;
  packet << 3 << thisPlayerID << postion_x << position_y;
  packet << static_cast<int>(moving_dir);
  if(connected)
  {
    socket->send(packet);
  }
}

void Client::sendPlayerDisconnect()
{
  sf::Packet packet;
  packet << 4;
  packet << thisPlayerID;
  if(connected)
  {
    socket->send(packet);
  }
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

void Client::sendPlayerShot(int bulletID, float playerPosX, float playerPosY, sf::Vector2f& shotDirection, float shot_angle)
{
  bullets.emplace_back(std::make_unique<Bullet>(thisPlayerID,bulletID, playerPosX, playerPosY, shotDirection, shot_angle));

  sf::Packet packet;
  packet << 5;
  packet << thisPlayerID;
  packet << bulletID << shotDirection.x << shotDirection.y << playerPosX << playerPosY << shot_angle;
  if(connected)
  {
    socket->send(packet);
  }
}

void Client::sendEnterGame(std::string& username, UserData::characterSkin skin, bool exitCurrentGame, int kill_num)
{
  otherplayersData.clear();
  sf::Packet packet;
  packet << 8;
  packet << username;
  packet << static_cast<int>(skin);
  packet << thisPlayerID;
  packet << exitCurrentGame;
  packet<< kill_num;
  if(connected)
  {
    socket->send(packet);
  }
}

void Client::sendPlayerRespawned()
{
  sf::Packet packet ;
  packet << 11;
  packet << thisPlayerID;
  if(connected)
  {
    socket->send(packet);
  }
}

void Client::receivePacket()
{
  while (running && connected)
  {
    sf::Packet packet;
    int packetID;
    while (connected)
    {
      auto status = socket->receive(packet);

      if(status == sf::Socket::Status::Disconnected)
      {
        connected = false;
        std::cout << "clean disconnection" << std::endl;
        socket->disconnect();
        break ;
      }
      else
      {
        packet >> packetID;
        // Packet 0 is when new player join
        if(packetID == 0)
        {
          if(gameState == GameState::LOBBY)
          {
            int skinNum;
            packet >> username >> skinNum >>myKills >> otherPlayerID;
            characterSkin = static_cast<UserData::characterSkin>(skinNum);
            chatText = std::move("[" + username + " joined the game]");
            std::cout << "Player" << otherPlayerID <<" joined" << std::endl;
            otherplayersData.emplace(otherplayersData.begin(),std::make_unique<UserData>(username,characterSkin, otherPlayerID, myKills));
            playerSpawn = true;
          }
        }
        // Packet 1 is receiving the existed playersdata' data in the game
        else if(packetID == 1)
        {
          if(gameState == GameState::LOBBY)
          {
            int skinNum;
            packet >> thisPlayerID;
            std::cout << "You are Player" << thisPlayerID  << std::endl;
            while (packet >> otherPlayerID >> username >> skinNum)
            {
              characterSkin = static_cast<UserData::characterSkin>(skinNum);
              otherplayersData.emplace(otherplayersData.begin(), std::make_unique<UserData>(username,characterSkin, otherPlayerID,myKills));
            }
            getExistedPlayers = true;
          }
        }
        // Packet 2 is receiving chat message
        else if(packetID == 2)
        {
          int gameStateID;
          packet >> gameStateID;
          if(gameState == static_cast<GameState::gameState>(gameStateID))
          {
            packet >> chatText;
          }
        }

        // Packet 3 is receiving player position
        else if(packetID == 3)
        {
          int movedPlayerID;
          float positionX;
          float positionY;
          int playerDirID;
          packet >> movedPlayerID;
          for(auto& data :otherplayersData)
          {
            if(data->getPLayerID() == movedPlayerID)
            {
              packet >> positionX >> positionY >> playerDirID;
              data->setPositionX(positionX);
              data->setPositionY(positionY);
              UserData::movingDir playerDir = static_cast<UserData::movingDir>(playerDirID);
              data->setMovingDir(playerDir);
            }
          }
        }

        else if(packetID ==4)
        {
          int disconnectedPLayerID;
          packet >>disconnectedPLayerID;
          for(auto& data :otherplayersData)
          {
            if(data->getPLayerID() == disconnectedPLayerID)
            {
              //std::cout << "Player" <<disconnectedPLayerID << " disconnected" << std::endl;
              int dataPos = find(otherplayersData.begin(), otherplayersData.end(), data) - otherplayersData.begin();
              otherplayersData.erase(otherplayersData.begin()+ dataPos);
            }
          }
        }

        else if(packetID == 5)
        {
          if(gameState == GameState::IN_GAME)
          {
            int playerID;
            int bulletID;
            float shotDirX;
            float shotDirY;
            float shotPosX;
            float shotPosY;
            float shotAngle;
            packet >> playerID >> bulletID >> shotDirX >> shotDirY >>
              shotPosX >> shotPosY >> shotAngle;
            sf::Vector2f shotDir = sf::Vector2f(shotDirX, shotDirY);

            otherBullets.emplace(
              otherBullets.begin(),
              std::make_unique<Bullet>(
                playerID, bulletID, shotPosX, shotPosY, shotDir, shotAngle));
            // std::cout <<"other bullet list: " << otherBullets.size() << std::endl;
            bulletSpawn = true;
          }
        }

        /*else if (packetID ==6)
        {
          int playerID;
          int bulletID;
          float shotPosX;
          float shotPosY;
          packet >> playerID >> bulletID >> shotPosX >> shotPosY ;
          //std::cout<< "bulletPos: " << shotPosX << " "<< shotPosY <<std::endl;
          for(auto& bullet : bullets)
          {
            if(bullet->getOwnerID() == playerID && bullet->getBulletID() == bulletID)
            {
              bullet->GetSprite()->setPosition(shotPosX, shotPosY);
            }
          }
        }*/
        else if(packetID == 7)
        {
          int playerID;
          int bulletID;
          packet >> playerID >> bulletID;

            if(playerID == thisPlayerID)
            {
              for (auto& bullet : bullets)
              {
                if(bullet!= nullptr)
                {
                  if (bullet->getBulletID() == bulletID)
                  {
                    bullet->setHitBool(true);
                  }
                }
              }
            }
            else
            {
              for(auto& otherbullet : otherBullets)
              {
                if(otherbullet != nullptr)
                {
                  if(otherbullet->getOwnerID() == playerID && otherbullet->getBulletID() == bulletID)
                  {
                    otherbullet->setHitBool(true);
                  }
                }
              }
            }
        }

        else if(packetID == 8)
        {
          int skinNum;
          int playerID;
          bool playerExitCurrentGame;
          int killNum;
          packet >> username >> skinNum >> playerID >> playerExitCurrentGame >> killNum;
          characterSkin = static_cast<UserData::characterSkin>(skinNum);

          if(gameState == GameState::IN_GAME)
          {
            chatText = std::move("[" + username + " joined the game]");
            std::cout << "Player" << playerID <<" joined" << std::endl;
            otherplayersData.emplace(otherplayersData.begin(),std::make_unique<UserData>(username,characterSkin, playerID, killNum));
            playerSpawn = true;
          }

          else if(gameState == GameState::LOBBY)
          {
            for(auto& playersInLobby : otherplayersData)
            {
              if(playersInLobby->getPLayerID() == playerID)
              {
                playersInLobby->setExitCurrentGame(playerExitCurrentGame);
              }
            }
          }
        }

        else if(packetID == 9)
        {
          packet >> spawnID;
          int skinNum;
          while (packet >> otherPlayerID >> username >> skinNum >> killnum)
          {
            characterSkin = static_cast<UserData::characterSkin>(skinNum);
            otherplayersData.emplace(otherplayersData.begin(),std::make_unique<UserData>(username,characterSkin, otherPlayerID, killnum));
          }
          getExistedPlayers_match = true;
        }

        else if(packetID == 10)
        {
          int id;
          int hp;
          packet >> id >> hp;
          std::cout << id << " " << hp << std::endl;

          if(thisPlayerID == id)
          {
            myHealth = hp;
            if(myHealth <=0)
            {
              packet >> playerDead;
              packet >> spawnID;
              std::cout << "RespawnID: " << spawnID << std::endl;
              myHealth = 3;
            }
            myHealthChange = true;
          }

          for(auto& player: otherplayersData)
          {
            if(player->getPLayerID() == id)
            {
              player->sethealth(hp);
            }
          }
          healthChange = true;
        }

        else if(packetID == 12)
        {
          int ID;
          int killNum;

          packet >> ID >> killNum;

          if(thisPlayerID == ID)
          {
            myKills = killNum;
          }
          for(auto& player: otherplayersData)
          {
            if(player->getPLayerID() == ID)
            {
              player->setNumOfKills(killNum);
            }
          }
          scoreUpdate = true;

        }
      }
    }
  }
}

void Client::disconnect()
{
  while (connected)
  {
    socket->disconnect();
    connected = false;
    std::cout << "clean disconnection" << std::endl;
  }

}