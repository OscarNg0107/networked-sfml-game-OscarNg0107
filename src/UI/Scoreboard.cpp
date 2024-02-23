//
// Created by OscarNg on 2023/12/5.
//

#include "Scoreboard.h"
Scoreboard::Scoreboard()
{
  panel_base = std::make_unique<sf::RectangleShape>();
  title_player = std::make_unique<Text>();
  killIcon_texture = std::make_unique<sf::Texture>();
  killIcon = std::make_unique<GameObject>();
}

void Scoreboard::init(const sf::Font& font, Camera& camera)
{
  panel_base->setSize(sf::Vector2f (500,350));

  panel_base->setFillColor(sf::Color(100,100,100,200));

  title_player->init("Players", font,25);
  title_player->getText()->setFillColor(sf::Color::White);


  if(!killIcon_texture->loadFromFile("Data/Images/UI/Skillicon7_19.png"))
  {
    std::cout << "Sprite texture loading error" << std::endl;
  }

  killIcon->initSprite(*killIcon_texture);
}

void Scoreboard ::update(Camera& camera)
{
  panel_base->setPosition(camera.getCamera()->getCenter().x - panel_base->getSize().x/2 ,
                          camera.getCamera()->getCenter().y - panel_base->getSize().y/2 );

  title_player->getText()->setPosition(panel_base->getPosition().x + 100,
                                       panel_base->getPosition().y + 10);

  killIcon->GetSprite()->setPosition(panel_base->getPosition().x + 362,
                                     panel_base->getPosition().y + 15);

  for(int i = 0; i< playerlist.size() ; ++i)
  {
    playerlist[i]->setPosition(panel_base->getPosition().x + panel_base->getGlobalBounds().width /2 - playerlist[i]->getBlockSize().x /2,
                               panel_base->getPosition().y + 50 + playerlist[i]->getBlockSize().y * i);
  }

  bubbleSort(playerlist);
}

void Scoreboard::keyPressed(sf::Event event)
{
  if (event.key.code == sf::Keyboard::Tab)
  {
    isVisible = true;
  }
}

void Scoreboard::keyReleased(sf::Event event)
{
  if (event.key.code == sf::Keyboard::Tab)
  {
    isVisible = false;
  }
}

std::vector<std::unique_ptr<ScoreboardBlock>>& Scoreboard::getPlayerList()
{
  return playerlist;
}

void Scoreboard::addPlayer(std::string& name, const sf::Font& font, UserData::characterSkin skin, int ID, int kill_num)
{
  playerlist.emplace_back(std::make_unique<ScoreboardBlock>(name,font,skin, ID, kill_num));
}

void Scoreboard::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  if(isVisible)
  {
    target.draw(*panel_base);
    target.draw(*title_player->getText());
    target.draw(*killIcon->GetSprite());

    for(auto& block : playerlist)
    {
      target.draw(*block);
    }
  }
}

void Scoreboard::bubbleSort(std::vector<std::unique_ptr<ScoreboardBlock>>& players)
{
  int listSize = players.size();
  ScoreboardBlock tmp;

  for(int i = 0; i < listSize; ++i)
  {
    for(int j =0 ; j < listSize - 1; ++j)
    {
      if(players[j]->getKillNum() < players[j +1]->getKillNum() )
      {
        players[j].swap(players[j+1]);
      }
    }

  }
}