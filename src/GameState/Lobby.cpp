//
// Created by OscarNg on 2023/10/20.
//

#include "Lobby.h"
#include <iostream>

Lobby::Lobby()
{

}
void Lobby::init(std::string& player_name, UserData::characterSkin player_skin, unsigned int windowSizeX, unsigned int windowSizeY, const sf::Font& font)
{
  map_lobby = std::make_unique<Tilemap>();
  player = std::make_unique<Player>();
  chatroom = std::make_unique<Chatroom>();
  pauseMenu = std::make_unique<PauseMenu>();

 map_lobby->initMap("Data/Lobby map.tmx", "Data/atlas_32x.png");

 player->init(player_name,player_skin, font, map_lobby->getMapSizeX()/2,map_lobby->getMapSizeY()/2 ,windowSizeX, windowSizeY);

 chatroom->init(font);

 pauseMenu->init(3,font,30);
 pauseMenu->addOptions("Return", font, 20);
 pauseMenu->addOptions("Return Main Menu", font, 20);
 pauseMenu->addOptions("Quit", font, 20);
}

void Lobby::update(float dt, Client& client, const sf::Font& font,std::vector<std::shared_ptr<UserData>>& otherplayersData)
{
  if(!chatroom->getIsOpened() && !pauseMenu->getIsOpened())
  {
    player->update( *map_lobby,dt);
  }
  client.sendPlayerPosition(player->GetSprite()->getPosition().x, player->GetSprite()->getPosition().y, player->getPlayerDir());

  chatroom->update(client, *player->getCamera());

  pauseMenu->update();

  for(auto & i : otherplayersData)
  {
    if(client.playerSpawn)
    {
      otherplayers.emplace_back(std::make_unique<Player>(i->getPLayerID(), i->getUserName(), i->getCharSkin(), font, *map_lobby));
      std::cout << otherplayers.size() << std::endl;
      client.playerSpawn = false;
    }
  }

  if(client.getExistedPlayers)
  {
    for(auto & i : otherplayersData)
    {
      otherplayers.emplace_back(std::make_unique<Player>(i->getPLayerID(), i->getUserName(), i->getCharSkin(), font, *map_lobby));
      std::cout << otherplayers.size() << std::endl;
    }
  }
  client.getExistedPlayers = false;



  for(auto& otherPlayerData : client.otherplayersData)

  {
    if( otherPlayerData!= nullptr)
    {
      for(auto & otherplayer : otherplayers)
      {
        if(otherplayer != nullptr)
        {
          if(otherplayer->getUserdata().getPLayerID() == otherPlayerData->getPLayerID())
          {
            otherplayer->GetSprite()->setPosition(otherPlayerData->getPostionX(), otherPlayerData->getPostionY());
            otherplayer->getNameText()->getText()->setPosition(otherPlayerData->getPostionX() + otherplayer->GetSprite()->getGlobalBounds().width/2
                                                                 -otherplayer->getNameText()->getText()->getGlobalBounds().width/2,
                                                               otherPlayerData->getPostionY() - otherplayer->getNameText()->getText()->getGlobalBounds().height * 1.5);
            otherplayer->animation(otherPlayerData->getMovingDir());


            if(otherPlayerData->getExitCurrentGame())
            {
              int pos = find(otherplayers.begin(), otherplayers.end(), otherplayer) - otherplayers.begin();
              otherplayers.erase(otherplayers.begin() + pos);
              std::cout << otherplayers.size() << std::endl;

              int pos_inClient = find(client.otherplayersData.begin(), client.otherplayersData.end(), otherPlayerData) - client.otherplayersData.begin();
              client.otherplayersData.erase(client.otherplayersData.begin() + pos_inClient);
              std::cout <<  client.otherplayersData.size() << std::endl;
            }
          }
        }
      }
    }
  }



  for(auto & i : map_lobby->getTilemap()[2])
  {
    if(player->GetSprite()->getGlobalBounds().intersects(i->GetSprite()->getGlobalBounds())
        && i->GetID()!= 0)
    {
      startGame = true;
    }
  }
}


void Lobby::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.setView(*player->getCamera()->getCamera());
  target.draw(*map_lobby);
  for(int i =0; i< otherplayers.size(); ++i)
  {
    target.draw(*otherplayers[i]->GetSprite());
    target.draw(*otherplayers[i]->getNameText()->getText());
  }
  target.draw(*player->GetSprite());
  target.draw(*player->getNameText()->getText());
  target.draw(*chatroom);
  target.draw(*pauseMenu);
}

void Lobby::mouseWheelMoved(sf::Event event)
{
  chatroom->mouseWheelMoved(event);
}

int Lobby::keyPressed(sf::Event event,std::string& username, Client& client, const sf::Font& font)
{
  if(!chatroom->getIsOpened() && !pauseMenu->getIsOpened())
  {
    player->keyPressed(event);
  }

  if(!pauseMenu->getIsOpened())
  {
    chatroom->KeyPressed(event, username, client);
  }

  if(!chatroom->getIsOpened())
  {
    return pauseMenu->keyPressed(event,*player->getCamera(), font);
  }
  return -1;
}

void Lobby::keyReleased(sf::Event event)
{
  player->keyReleased(event);
  chatroom->KeyReleased(event, *player->getCamera());
}

void Lobby::TextEntered(sf::Event event)
{
  chatroom->TextEntered(event);
}

void Lobby::resetLobbyData()
{
  player= nullptr;
  chatroom= nullptr;
  pauseMenu = nullptr;
  otherplayers.clear();
}


bool Lobby::isStartGame()
{
  return startGame;
}
void Lobby::setIsStartGame(bool boolean)
{
  startGame = boolean;
}
