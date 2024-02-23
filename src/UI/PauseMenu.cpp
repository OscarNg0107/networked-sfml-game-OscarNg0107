//
// Created by OscarNg on 2023/11/26.
//

#include "PauseMenu.h"
PauseMenu::PauseMenu()
{
  pauseTitle = std::make_unique<Text>();
  optionPanel = std::make_unique<sf::RectangleShape>();
  bgPanel = std::make_unique<sf::RectangleShape>();
}

void PauseMenu::init(int NumOfElements, const sf::Font& font, unsigned int textsize)
{
  listSize = NumOfElements;
  option_lists.reserve(listSize);

  bgPanel->setSize(sf::Vector2f (1920,1080));
  bgPanel->setFillColor(sf::Color(0,0,0,100));
  bgPanel->setPosition(0,0);

  optionPanel->setFillColor(sf::Color(200,200,200,125));

  pauseTitle->init("Game Menu", font, textsize);
  pauseTitle->getText()->setFillColor(sf::Color(255,255,255,255));
}

void PauseMenu::setPosition(Camera& camera, const sf::Font& font)
{
  pauseTitle->getText()->setPosition(camera.getCamera()->getCenter().x - pauseTitle->getText()->getGlobalBounds().width/2,
                                     camera.getCamera()->getCenter().y - pauseTitle->getText()->getGlobalBounds().height * 3);
  for(int i =0; i < option_lists.size(); ++i)
  {
    option_lists[i]->getText()->setPosition(camera.getCamera()->getCenter().x - option_lists[i]->getText()->getGlobalBounds().width/2,
                                            pauseTitle->getText()->getPosition().y + pauseTitle->getText()->getGlobalBounds().height* 2 +
                                              font.getLineSpacing(20) * i);
  }
  optionPanel->setSize(sf::Vector2f (300,
                                    option_lists.back()->getText()->getPosition().y + option_lists.back()->getText()->getGlobalBounds().height * 1.1
                                      - pauseTitle->getText()->getPosition().y + pauseTitle->getText()->getGlobalBounds().height * 0.3));
  optionPanel->setPosition(camera.getCamera()->getCenter().x - optionPanel->getGlobalBounds().width/2 ,
                           pauseTitle->getText()->getPosition().y - pauseTitle->getText()->getGlobalBounds().height * 0.1);
}

void PauseMenu::update()
{
  if(isOpened)
  {
    for(auto& option : option_lists)
    {
      int optionPos = find(option_lists.begin(), option_lists.end(), option) - option_lists.begin();
      option_lists[optionPos]->getText()->setFillColor(sf::Color(255,255,255,125));
      if(option_selected % listSize == optionPos)
      {
        option_lists[optionPos]->getText()->setFillColor(sf::Color(255,255,255,255));
      }
    }
  }

}

int PauseMenu::keyPressed(sf::Event event,Camera& camera, const sf::Font& font)
{
  if(event.key.code == sf::Keyboard::Escape)
  {
    isOpened = !isOpened;
    std::cout << isOpened << std::endl;
    setPosition(camera, font);
  }

  if(isOpened)
  {
    if(event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W)
    {
      option_selected -=1;
      if(option_selected < 0)
      {
        option_selected = listSize -1;
      }
    }

    if(event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S)
    {
      option_selected +=1;
    }

    if(event.key.code == sf::Keyboard::Enter)
    {
      for(int i = 0; i < listSize; ++i)
      {
        if(option_selected % option_lists.size() == i)
        {
          isOpened = false;
          return i;
        }
      }
    }
  }
  return -1;
}

void PauseMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  if(isOpened)
  {
    target.draw(*bgPanel);
    target.draw(*optionPanel);
    target.draw(*pauseTitle->getText());
    for(auto& option : option_lists)
    {
      target.draw(*option->getText());
    }
  }
}

void PauseMenu::addOptions(std::string option_text, const sf::Font& font, unsigned int size)
{
  option_lists.emplace_back(std::make_unique<Text>(option_text, font,size));
}

bool PauseMenu::getIsOpened()
{
  return isOpened;
}

void PauseMenu::setIsOpened(bool boolean)
{
  isOpened = boolean;
}