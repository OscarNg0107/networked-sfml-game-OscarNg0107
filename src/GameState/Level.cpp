//
// Created by OscarNg on 2023/10/28.
//

#include "Level.h"

Level::Level()
{
  map_level = std::make_unique<Tilemap>();
  player = std::make_unique<Player>();
  chatroom = std::make_unique<Chatroom>();
  pauseMenu = std::make_unique<PauseMenu>();
  healthBar = std::make_unique<HealthBar>();
  scoreboard = std::make_unique<Scoreboard>();
  shot_coolDown = std::make_unique<sf::Clock>();

  //test = std::make_unique<NPC>();
}

void Level::init(std::string& player_name, UserData::characterSkin player_skin, int spawnID, unsigned int windowSizeX, unsigned int windowSizeY, const sf::Font& font)
{
  //map_level->initMap("Data/Map/Level Map.tmx", "Data/Map/png/streets tiles 2.png");
  map_level->initMap("Data/Map/Match Map.tmx", "Data/Map/png/streets tiles 2.png");

  chatroom->init(font);

  pauseMenu->init(3,font,30);
  pauseMenu->addOptions("Return", font, 20);
  pauseMenu->addOptions("Return Main Menu", font, 20);
  pauseMenu->addOptions("Quit", font, 20);

  player->init(player_name,player_skin, font, map_level->getSpawnPoints()[0][spawnID]->getPositionX(), map_level->getSpawnPoints()[0][spawnID]->getPositionY(), windowSizeX, windowSizeY);
  healthBar->init(player->getHealth(),player_skin, 2.5f);
  healthBar->setPostion(*player->getCamera());

  scoreboard->init(font, *player->getCamera());
  scoreboard->addPlayer(player_name,font,player_skin, player->getUserdata().getPLayerID(), player->getUserdata().getNumOfKills());

 /* test->test_texture.loadFromFile("Data/Images/character/PNGS/Character singlesprite/female police.png");
  test->initSprite(test->test_texture);
  test->GetSprite()->setPosition(windowSizeX/2, windowSizeY/2);*/

}

void Level::update(float dt, Client& client , const sf::Font& font)
{
  if (!chatroom->getIsOpened() && !pauseMenu->getIsOpened())
  {
    player->update(*map_level, dt);
  }
  client.sendPlayerPosition(
    player->GetSprite()->getPosition().x,
    player->GetSprite()->getPosition().y,
    player->getPlayerDir());

  chatroom->update(client, *player->getCamera());

  pauseMenu->update();

  healthBar->setPostion(*player->getCamera());

  scoreboard->update(*player->getCamera());

  for (auto& i : client.otherplayersData)
  {
    if(client.playerSpawn)
    {
      otherplayers.emplace_back(std::make_unique<Player>(i->getPLayerID(), i->getUserName(), i->getCharSkin(), font, *map_level));
      std::cout << otherplayers.size() << std::endl;
      scoreboard->addPlayer(i->getUserName(),font,i->getCharSkin(), i->getPLayerID(), i->getNumOfKills());
      client.playerSpawn = false;
    }
  }

  if(client.getExistedPlayers_match)
  {
    for (auto& i : client.otherplayersData)
    {
      otherplayers.emplace_back(std::make_unique<Player>(i->getPLayerID(), i->getUserName(), i->getCharSkin(), font, *map_level));
      std::cout << otherplayers.size() << std::endl;
      scoreboard->addPlayer(i->getUserName(),font,i->getCharSkin(), i->getPLayerID(), i->getNumOfKills());
    }
    client.getExistedPlayers_match = false;
  }



  for (auto& otherplayer : otherplayers)
  {
    for (auto& otherPlayerData : client.otherplayersData)
    {
      if (
        otherplayer->getUserdata().getPLayerID() ==
        otherPlayerData->getPLayerID())
      {
        otherplayer->GetSprite()->setPosition(
          otherPlayerData->getPostionX(), otherPlayerData->getPostionY());
        otherplayer->getNameText()->getText()->setPosition(
          otherPlayerData->getPostionX() +
            otherplayer->GetSprite()->getGlobalBounds().width / 2 -
            otherplayer->getNameText()->getText()->getGlobalBounds().width / 2,
          otherPlayerData->getPostionY() -
            otherplayer->getNameText()->getText()->getGlobalBounds().height *
              1.5);
        otherplayer->animation(otherPlayerData->getMovingDir());
      }
    }
  }

  for (auto& mybullet : bullets)
  {
    mybullet->update(dt, map_level->getTilemap());
  }

  for (auto& bullet : client.otherBullets)
  {
    if (client.bulletSpawn)
    {
      otherBullets.emplace_back(std::make_unique<Bullet>(
        bullet->getOwnerID(),
        bullet->getBulletID(),
        bullet->GetSprite()->getPosition().x,
        bullet->GetSprite()->getPosition().y,
        bullet->getMovingDir(),
        bullet->getAngle()));
    }
    client.bulletSpawn = false;
  }

  for (auto& otherBullet : otherBullets)
  {
    if (otherBullet != nullptr)
    {
      otherBullet->update(dt, map_level->getTilemap());

      for (auto& clientOtherBullet : client.otherBullets)
      {
        if (clientOtherBullet != nullptr)
        {
          // sometimes the client will crash in here
          if (clientOtherBullet->getHitBool())
          {
            if (
              clientOtherBullet->getOwnerID() == otherBullet->getOwnerID() &&
              clientOtherBullet->getBulletID() == otherBullet->getBulletID())
            {
              int pos =
                find(otherBullets.begin(), otherBullets.end(), otherBullet) -
                otherBullets.begin();
              otherBullets.erase(otherBullets.begin() + pos);
            }
            int pos_client = find(
                               client.otherBullets.begin(),
                               client.otherBullets.end(),
                               clientOtherBullet) -
                             client.otherBullets.begin();
            client.otherBullets.erase(client.otherBullets.begin() + pos_client);
          }
        }
      }
    }
  }

  for (auto& clientBullet : client.bullets)
  {
    if (clientBullet->getHitBool())
    {
      for (auto& bullet : bullets)
      {
        if (bullet != nullptr)
        {
          if (clientBullet->getBulletID() == bullet->getBulletID())
          {
            int pos =
              find(bullets.begin(), bullets.end(), bullet) - bullets.begin();
            bullets.erase(bullets.begin() + pos);
          }
        }
      }
    }
  }

  if(client.healthChange)
  {
    if(client.myHealthChange)
    {
      player->setHealth(client.myHealth);
      healthBar->healthchanged(client.myHealth);
      client.myHealthChange = false;
    }

    for (auto& otherplayer : otherplayers)
    {
      for (auto& otherPlayerData : client.otherplayersData)
      {
        if (otherplayer->getUserdata().getPLayerID() == otherPlayerData->getPLayerID())
        {
          otherplayer->setHealth(otherPlayerData->getHealth());
        }
      }
    }
    client.healthChange = false;
  }

  if(client.playerDead)
  {
    std::cout << "RespawnID in Level: " << client.spawnID<< std::endl;
    player->GetSprite()->setPosition(map_level->getSpawnPoints()[0][client.spawnID]->getPositionX(), map_level->getSpawnPoints()[0][client.spawnID]->getPositionY());
    player->getCamera()->getCamera()->setCenter(player->GetSprite()->getPosition().x + player->GetSprite()->getGlobalBounds().width/2,
                                                player->GetSprite()->getPosition().y + player->GetSprite()->getGlobalBounds().height/2);
    healthBar->resetHealthBar(2.5);
    client.sendPlayerRespawned();
  }
  client.playerDead = false;

  if(client.scoreUpdate)
  {
    for(auto& block : scoreboard->getPlayerList())
    {
      if(block->getPlayerID() == player->getUserdata().getPLayerID())
      {
        block->setKillNum(client.myKills);
      }
      for(auto& clientPData : client.otherplayersData)
      {
        if(block->getPlayerID() == clientPData->getPLayerID())
        {
          block->setKillNum(clientPData->getNumOfKills());
        }
      }
    }
  }
  client.scoreUpdate = false;
}


void Level::mouseClicked(sf::Event event, Client& client,float clickX, float clickY)
{
  if(event.mouseButton.button == sf::Mouse::Left)
  {
    if(shot_coolDown->getElapsedTime().asSeconds() > 0.5)
    {
      bulletIDsetter ++;
      bullets.emplace_back(std::make_unique<Bullet>(bulletIDsetter,player->GetSprite()->getPosition().x + player->GetSprite()->getGlobalBounds().width /2,
                                                    player->GetSprite()->getPosition().y + player->GetSprite()->getGlobalBounds().height/2,clickX, clickY));
      client.sendPlayerShot(
        bullets.back()->getBulletID(),player->GetSprite()->getPosition().x, player->GetSprite()->getPosition().y,
        bullets.back()->getMovingDir(), bullets.back()->getAngle());
      shot_coolDown->restart();
    }
  }
}

void Level::mouseWheelMoved(sf::Event event)
{
  chatroom->mouseWheelMoved(event);
}

int Level::keyPressed(sf::Event event,std::string& username, Client& client, const sf::Font& font)
{
  if(!chatroom->getIsOpened() && !pauseMenu->getIsOpened())
  {
    player->keyPressed(event);
  }

  scoreboard->keyPressed(event);

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

void Level::keyReleased(sf::Event event)
{
  player->keyReleased(event);
  chatroom->KeyReleased(event, *player->getCamera());
  scoreboard->keyReleased(event);
}

void Level::TextEntered(sf::Event event)
{
  chatroom->TextEntered(event);
}

void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.setView(*player->getCamera()->getCamera());
  target.draw(*map_level);
  for(int i =0; i< otherplayers.size(); ++i)
  {
    target.draw(*otherplayers[i]->GetSprite());
    target.draw(*otherplayers[i]->getNameText()->getText());
  }
  target.draw(*player->GetSprite());
  target.draw(*player->getNameText()->getText());


  for(auto& bullet : bullets)
  {
    target.draw(*bullet->GetSprite());
  }
  for(auto& otherBullet : otherBullets)
  {
    target.draw(*otherBullet->GetSprite());
  }
  target.draw(*chatroom);
  target.draw(*healthBar);
  target.draw(*scoreboard);
  target.draw(*pauseMenu);

}

std::unique_ptr<Tilemap>& Level::getMap()
{
  return map_level;
}