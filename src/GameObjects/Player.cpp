//
// Created by OscarNg on 2023/10/21.
//

#include "Player.h"
#include <iostream>

Player::Player()
{
  character_texture = std::make_unique<sf::Texture>();
  character_texture_rect = std::make_unique<sf::IntRect>();
  character_anim_clock = std::make_unique<sf::Clock>();
  username_text = std::make_unique<Text>();
}

Player::Player(int playerID, std::string& username, UserData::characterSkin skin, const sf::Font& font, Tilemap& map) : Player()
{
  playerData.setUserName(username);
  playerData.setPlayerID(playerID);
  switch (skin)
  {
    case UserData::DAVID:
      character_texture->loadFromFile("Data/Images/character/PNGS/davidmartinez.png");
      break ;
    case UserData::LUCY:
      character_texture->loadFromFile("Data/Images/character/PNGS/lucy.png");
      break ;
    case UserData::REBECCA:
      character_texture->loadFromFile("Data/Images/character/PNGS/rebecca.png");
      break ;
  }
  initSprite(*character_texture);
  *character_texture_rect = sf::IntRect(0 , 0, character_texture->getSize().x /4 , character_texture->getSize().y /4);
  GetSprite()->setTextureRect(*character_texture_rect);

  hitbox();
  GetSprite()->setPosition(map.getMapSizeX()/2 , map.getMapSizeY()/2);

  setHealth(3);

  username_text->init("<" +username+ ">", font, 8);
  username_text->getText()->setFillColor(sf::Color(255,255,255,255));
  username_text->getText()->setPosition(GetSprite()->getPosition().x + GetSprite()->getGlobalBounds().width/2 - username_text->getText()->getGlobalBounds().width/2,
                                        GetSprite()->getPosition().y - username_text->getText()->getGlobalBounds().height * 1.5);

}

Player::Player(int playerID, std::string& username, UserData::characterSkin skin) :Player()
{
  playerData.setUserName(username);
  playerData.setPlayerID(playerID);
  switch (skin)
  {
    case UserData::DAVID:
      character_texture->loadFromFile("Data/Images/character/PNGS/davidmartinez.png");
      break ;
    case UserData::LUCY:
      character_texture->loadFromFile("Data/Images/character/PNGS/lucy.png");
      break ;
    case UserData::REBECCA:
      character_texture->loadFromFile("Data/Images/character/PNGS/rebecca.png");
      break ;
  }
  initSprite(*character_texture);
  *character_texture_rect = sf::IntRect(0 , 0, character_texture->getSize().x /4 , character_texture->getSize().y /4);
  GetSprite()->setTextureRect(*character_texture_rect);

  setHealth(3);

  hitbox();
}

void Player::init(std::string& username, UserData::characterSkin skin ,const sf::Font& font, float posX, float posY, unsigned int windowSizeX, unsigned int windowSizeY)
{
  camera = std::make_unique<Camera>();
  playerData.setUserName(username);
  switch (skin)
  {
    case UserData::DAVID:
      character_texture->loadFromFile("Data/Images/character/PNGS/davidmartinez.png");
      break ;
    case UserData::LUCY:
      character_texture->loadFromFile("Data/Images/character/PNGS/lucy.png");
      break ;
    case UserData::REBECCA:
      character_texture->loadFromFile("Data/Images/character/PNGS/rebecca.png");
      break ;
  }
  initSprite(*character_texture);
  *character_texture_rect = sf::IntRect(0 , 0, character_texture->getSize().x /4 , character_texture->getSize().y /4);
  GetSprite()->setTextureRect(*character_texture_rect);
  setHealth(3);
  GetSprite()->setPosition(posX, posY);
  username_text->init("<" +username+ ">", font, 8);
  username_text->getText()->setFillColor(sf::Color(255,255,255,255));
  username_text->getText()->setPosition(GetSprite()->getPosition().x + GetSprite()->getGlobalBounds().width/2 - username_text->getText()->getGlobalBounds().width/2,
                                        GetSprite()->getPosition().y - username_text->getText()->getGlobalBounds().height * 1.5);
  camera->initCamera(windowSizeX, windowSizeY, *GetSprite());
  camera->getCamera()->zoom(0.4);
}

void Player::update(Tilemap& tilemap, float dt)
{
  hitbox();
  GetSprite()->move(getMovingDir());
  camera->MoveCamera(dt,*GetSprite(), getMovingDir(), tilemap.getTilemap());

  animation(playerDir);

  if(!isMovingUp && !isMovingDown && !isMovingLeft && !isMovingRight)
  {
    playerDir = UserData::NONE;
  }

  if (playerDir == UserData::LEFT)
  {
    setMovingDir(-1,0);
  }
  if(playerDir == UserData::RIGHT)
  {
    setMovingDir(1,0);
  }
  if (playerDir == UserData::UP)
  {
    setMovingDir(0,-1);
  }
  if (playerDir == UserData::DOWN)
  {
    setMovingDir(0,1);
  }
  if(playerDir == UserData::NONE)
  {
    setMovingDir(0,0);
  }

  if(GetSprite()->getPosition().x <= tilemap.getTilemap()[0][0]->GetSprite()->getPosition().x)
  {
    GetSprite()->setPosition( tilemap.getTilemap()[0][0]->GetSprite()->getPosition().x, GetSprite()->getPosition().y);
  }

  if(GetSprite()->getPosition().x + GetSprite()->getGlobalBounds().width >=
      tilemap.getTilemap()[0][tilemap.getTilemap()[0].size()-2]->GetSprite()->getPosition().x +
        tilemap.getTilemap()[0][tilemap.getTilemap()[0].size()-2]->GetSprite()->getGlobalBounds().width)
  {
    GetSprite()->setPosition(tilemap.getTilemap()[0][tilemap.getTilemap()[0].size()-2]->GetSprite()->getPosition().x +
                               tilemap.getTilemap()[0][tilemap.getTilemap()[0].size()-2]->GetSprite()->getGlobalBounds().width -
                               GetSprite()->getGlobalBounds().width ,GetSprite()->getPosition().y);
  }

  if(GetSprite()->getPosition().y <= tilemap.getTilemap()[0][0]->GetSprite()->getPosition().y)
  {
    GetSprite()->setPosition(GetSprite()->getPosition().x, tilemap.getTilemap()[0][0]->GetSprite()->getPosition().y);
  }

  if(GetSprite()->getPosition().y + GetSprite()->getGlobalBounds().height >=
      tilemap.getTilemap()[0][tilemap.getTilemap()[0].size()-2]->GetSprite()->getPosition().y +
        tilemap.getTilemap()[0][tilemap.getTilemap()[0].size()-2]->GetSprite()->getGlobalBounds().height)
  {
    GetSprite()->setPosition(GetSprite()->getPosition().x, tilemap.getTilemap()[0][tilemap.getTilemap()[0].size()-2]->GetSprite()->getPosition().y
                                                             + tilemap.getTilemap()[0][tilemap.getTilemap()[0].size()-2]->GetSprite()->getGlobalBounds().height -
                                                             GetSprite()->getGlobalBounds().height);
  }

  for(int i=0 ; i < tilemap.getEmptyTiles(0).size() ;  ++i)
  {
    if(getTopHitbox()->intersects(tilemap.getEmptyTiles(0)[i].getGlobalBounds()) &&getMovingDir().y < 0)
    {
      GetSprite()->setPosition(GetSprite()->getPosition().x, tilemap.getEmptyTiles(0)[i].getPosition().y + tilemap.getEmptyTiles(0)[i].getGlobalBounds().height);
    }
    if(getBottomHitbox()->intersects(tilemap.getEmptyTiles(0)[i].getGlobalBounds()) && getMovingDir().y > 0)
    {
      GetSprite()->setPosition(GetSprite()->getPosition().x, tilemap.getEmptyTiles(0)[i].getPosition().y - GetSprite()->getGlobalBounds().height);
    }
    if(getLeftHitbox()->intersects(tilemap.getEmptyTiles(0)[i].getGlobalBounds())&&getMovingDir().x < 0)
    {
      GetSprite()->setPosition(tilemap.getEmptyTiles(0)[i].getPosition().x + tilemap.getEmptyTiles(0)[i].getGlobalBounds().width, GetSprite()->getPosition().y);
    }
    if( getRightHitbox()->intersects(tilemap.getEmptyTiles(0)[i].getGlobalBounds()) && getMovingDir().x > 0)
    {
      GetSprite()->setPosition(tilemap.getEmptyTiles(0)[i].getPosition().x -GetSprite()->getGlobalBounds().width, GetSprite()->getPosition().y);
    }
  }

  if(tilemap.getTilemap().size() > 1)
  {
    for(int i = 1; i< tilemap.getTilemap().size(); ++i)
    {
      for(int j = 0; j < tilemap.getTilemap()[i].size(); ++j)
      {
        if(tilemap.getTilemap()[i][j]->GetID() !=0)
        {
          if(getTopHitbox()->intersects(tilemap.getTilemap()[i][j]->GetSprite()->getGlobalBounds()) &&getMovingDir().y < 0)
          {
            GetSprite()->setPosition(GetSprite()->getPosition().x,
                                     tilemap.getTilemap()[i][j]->GetSprite()->getPosition().y +
                                       tilemap.getTilemap()[i][j]->GetSprite()->getGlobalBounds().height);
          }
          if(getBottomHitbox()->intersects(tilemap.getTilemap()[i][j]->GetSprite()->getGlobalBounds()) && getMovingDir().y > 0)
          {
            GetSprite()->setPosition(GetSprite()->getPosition().x,
                                     tilemap.getTilemap()[i][j]->GetSprite()->getPosition().y -
                                       GetSprite()->getGlobalBounds().height);
          }
          if(getLeftHitbox()->intersects(tilemap.getTilemap()[i][j]->GetSprite()->getGlobalBounds())&&getMovingDir().x < 0)
          {
            GetSprite()->setPosition(tilemap.getTilemap()[i][j]->GetSprite()->getPosition().x +
                                       tilemap.getTilemap()[i][j]->GetSprite()->getGlobalBounds().width,
                                     GetSprite()->getPosition().y);
          }
          if( getRightHitbox()->intersects(tilemap.getTilemap()[i][j]->GetSprite()->getGlobalBounds()) && getMovingDir().x > 0)
          {
            GetSprite()->setPosition(tilemap.getTilemap()[i][j]->GetSprite()->getPosition().x -
                                       GetSprite()->getGlobalBounds().width,
                                     GetSprite()->getPosition().y);
          }
        }

      }
    }
  }

  username_text->getText()->setPosition(GetSprite()->getPosition().x + GetSprite()->getGlobalBounds().width/2 - username_text->getText()->getGlobalBounds().width/2,
                                        GetSprite()->getPosition().y - username_text->getText()->getGlobalBounds().height * 1.5);

}

void Player::animation(UserData::movingDir playerDirection)
{
  if (playerDirection == UserData::LEFT)
  {
    if(character_anim_clock->getElapsedTime().asSeconds() > 0.2)
    {
      character_texture_rect->top = character_texture->getSize().y /2;
      if(character_texture_rect->left >= character_texture->getSize().x * 3/4)
      {
        character_texture_rect->left = 0;
      }
      else
      {
        character_texture_rect->left += character_texture->getSize().x /4;
      }
      GetSprite()->setTextureRect(*character_texture_rect);
      character_anim_clock->restart();
    }
  }
  if(playerDirection == UserData::RIGHT)
  {
    if(character_anim_clock->getElapsedTime().asSeconds() > 0.2)
    {
      character_texture_rect->top = character_texture->getSize().y /4;
      if(character_texture_rect->left >= character_texture->getSize().x * 3/4)
      {
        character_texture_rect->left = 0;
      }
      else
      {
        character_texture_rect->left += character_texture->getSize().x /4;
      }
      GetSprite()->setTextureRect(*character_texture_rect);
      character_anim_clock->restart();
    }
  }
  if (playerDirection == UserData::UP)
  {
    if(character_anim_clock->getElapsedTime().asSeconds() > 0.2)
    {
      character_texture_rect->top = character_texture->getSize().y /4 * 3;
      if(character_texture_rect->left >= character_texture->getSize().x * 3/4)
      {
        character_texture_rect->left = 0;
      }
      else
      {
        character_texture_rect->left += character_texture->getSize().x /4;
      }
      GetSprite()->setTextureRect(*character_texture_rect);
      character_anim_clock->restart();
    }
  }
  if (playerDirection == UserData::DOWN)
  {
    if(character_anim_clock->getElapsedTime().asSeconds() > 0.2)
    {
      character_texture_rect->top = 0;
      if(character_texture_rect->left >= character_texture->getSize().x * 3/4)
      {
        character_texture_rect->left = 0;
      }
      else
      {
        character_texture_rect->left += character_texture->getSize().x /4;
      }
      GetSprite()->setTextureRect(*character_texture_rect);
      character_anim_clock->restart();
    }
  }
}


void Player::keyPressed(sf::Event event)
{
  if(event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up)
  {
    playerDir = UserData::UP;
    isMovingUp = true;
  }
  else if(event.key.code == sf::Keyboard::S|| event.key.code == sf::Keyboard::Down)
  {
    playerDir = UserData::DOWN;
    isMovingDown = true;
  }
  else if(event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left)
  {
    playerDir = UserData::LEFT;
    isMovingLeft = true;
  }
  else if(event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right)
  {
    playerDir = UserData::RIGHT;
    isMovingRight = true;
  }

  if(event.key.code == sf::Keyboard::Num1)
  {
    weaponUsing = EMPTY;
  }

  else if(event.key.code == sf::Keyboard::Num2)
  {
    weaponUsing = KNIFE;
  }
  else if(event.key.code == sf::Keyboard::Num3)
  {
    weaponUsing = PISTOL;
  }
}

void Player::keyReleased(sf::Event event)
{
  if(event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up)
  {
    isMovingUp = false;
  }

  if(event.key.code == sf::Keyboard::S|| event.key.code == sf::Keyboard::Down )
  {
    isMovingDown = false;
  }
  if(event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left)
  {
    isMovingLeft = false;
  }
  if(event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right)
  {
    isMovingRight = false;
  }
}

std::unique_ptr<Camera>& Player::getCamera()
{
  return camera;
}

UserData& Player::getUserdata()
{
  return playerData;
}

UserData::movingDir Player::getPlayerDir()
{
  return playerDir;
}

std::unique_ptr<Text>& Player::getNameText()
{
  return username_text;
}

void Player::setSpawned(bool boolean)
{
  isSpawned = boolean;
}

bool Player::getSpawned()
{
  return isSpawned;
}