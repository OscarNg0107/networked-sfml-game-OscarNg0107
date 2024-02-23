//
// Created by OscarNg on 2023/12/5.
//

#include "ScoreboardBlock.h"
ScoreboardBlock::ScoreboardBlock()
{
  panel_base = std::make_unique<sf::RectangleShape>();
  charIcon = std::make_unique<GameObject>();
  charIcon_texture = std::make_unique<sf::Texture>();
  text_username = std::make_unique<Text>();
  text_killNum = std::make_unique<Text>();
}

ScoreboardBlock::ScoreboardBlock(std::string& name,const sf::Font& font, UserData::characterSkin skin, int ID, int kill_num) : ScoreboardBlock()
{
  panel_base->setSize(sf::Vector2f (400, 35));
  panel_base->setFillColor(sf::Color(200,200,200,125));
  panel_base->setOutlineColor(sf::Color::Black);
  panel_base->setOutlineThickness(1);
  setKillNum(kill_num);

  switch (skin)
  {
    case UserData::DAVID:
      charIcon_texture->loadFromFile("Data/Images/character/PNGS/Character singlesprite/davidmartinez.png");
      break ;
    case UserData::LUCY:
      charIcon_texture->loadFromFile("Data/Images/character/PNGS/Character singlesprite/lucy.png");
      break ;
    case UserData::REBECCA:
      charIcon_texture->loadFromFile("Data/Images/character/PNGS/Character singlesprite/rebecca.png");
      break ;
  }

  charIcon->initSprite(*charIcon_texture);
  //charIcon->GetSprite()->setScale();

  text_username->init(name, font, 25);
  text_username->getText()->setFillColor(sf::Color::White);

  text_killNum->init("0", font, 25);
  text_killNum->getText()->setFillColor(sf::Color::White);
  setKillNum(kill_num);

  playerID = ID;
}

void ScoreboardBlock::init(std::string& name,const sf::Font& font, UserData::characterSkin skin, int ID, int kill_num)
{
  panel_base->setSize(sf::Vector2f (400, 35));
  panel_base->setFillColor(sf::Color(200,200,200,125));
  panel_base->setOutlineColor(sf::Color::Black);
  panel_base->setOutlineThickness(1);


  switch (skin)
  {
    case UserData::DAVID:
      charIcon_texture->loadFromFile("Data/Images/character/PNGS/Character singlesprite/davidmartinez.png");
      break ;
    case UserData::LUCY:
      charIcon_texture->loadFromFile("Data/Images/character/PNGS/Character singlesprite/lucy.png");
      break ;
    case UserData::REBECCA:
      charIcon_texture->loadFromFile("Data/Images/character/PNGS/Character singlesprite/rebecca.png");
      break ;
  }

  charIcon->initSprite(*charIcon_texture);
  //charIcon->GetSprite()->setScale();

  text_username->init(name, font, 25);
  text_username->getText()->setFillColor(sf::Color::White);

  text_killNum->init("0", font, 25);
  text_killNum->getText()->setFillColor(sf::Color::White);
  setKillNum(kill_num);

  playerID = ID;
}

void ScoreboardBlock::setPosition(float posX, float posY)
{
  panel_base->setPosition(posX, posY);
  charIcon->GetSprite()->setPosition(panel_base->getPosition().x + 20,
                                     panel_base->getPosition().y + panel_base->getGlobalBounds().height/2 - charIcon->GetSprite()->getGlobalBounds().height/2);
  text_username->getText()->setPosition(charIcon->GetSprite()->getPosition().x + charIcon->GetSprite()->getGlobalBounds().width + 20,
                                        panel_base->getPosition().y + panel_base->getGlobalBounds().height/2 - text_username->getText()->getGlobalBounds().height);
  text_killNum->getText()->setPosition(panel_base->getPosition().x + panel_base->getGlobalBounds().width * 4/5,
                                       panel_base->getPosition().y + panel_base->getGlobalBounds().height/2 - text_killNum->getText()->getGlobalBounds().height);
}

const sf::Vector2f& ScoreboardBlock::getBlockSize()
{
  return panel_base->getSize();
}

int ScoreboardBlock::getPlayerID()
{
  return playerID;
}

int ScoreboardBlock::getKillNum()
{
  return killNum;
}

void ScoreboardBlock::setKillNum(int kill_num)
{
  killNum = kill_num;
  std::stringstream killSs;
  killSs << kill_num;
  std::string killString = killSs.str();
  text_killNum->getText()->setString(killString);
}

void ScoreboardBlock::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(*panel_base);
  target.draw(*charIcon->GetSprite());
  target.draw(*text_username->getText());
  target.draw(*text_killNum->getText());
}