//
// Created by OscarNg on 2023/10/13.
//

#include "Menu.h"

Menu::Menu()
{
  title= std::make_unique<Text>();
  prompt_text_start = std::make_unique<Text>();
  start_text = std::make_unique<Text>();
  quit_text = std::make_unique<Text>();
  view = std::make_unique<Camera>();
}
void Menu::init(const sf::Font& font, unsigned int windowSizeX, unsigned int windowSizeY)
{
  view->getCamera()->setSize(1920, 1080);
  view->getCamera()->setCenter(960, 540);
  title->init("title", font, 100);
  title->getText()->setPosition(windowSizeX/2 - title->getText()->getGlobalBounds().width/2,windowSizeY/3);
  title->getText()->setFillColor(sf::Color(255,255,255,255));

  prompt_text_start->init("[Press Any Key To Continue]",font,60);
  prompt_text_start->getText()->setPosition(windowSizeX/2 - prompt_text_start->getText()->getGlobalBounds().width/2, windowSizeY/1.3);
  prompt_text_start->getText()->setFillColor(sf::Color(255,255,255,alphafading_text));

  start_text->init("start", font, 40);
  start_text->getText()->setPosition(windowSizeX/2 - start_text->getText()->getGlobalBounds().width/2, windowSizeY/1.5);
  start_text->getText()->setFillColor(sf::Color(255,255,255,alphaDefault_text));

  quit_text->init("Quit", font, 40);
  quit_text->getText()->setPosition(windowSizeX/2 - quit_text->getText()->getGlobalBounds().width/2, windowSizeY/ 1.4);
  quit_text->getText()->setFillColor(sf::Color(255,255,255,alphaDefault_text));
}

void Menu::update()
{
  if(!inMianMenu)
  {
    alphafading_text += fadingvalue;
    prompt_text_start->getText()->setFillColor(sf::Color(255,255,255,alphafading_text));
    if(alphafading_text >= 255 || alphafading_text <= 1)
    {
      fadingvalue *= -1;
    }

  }
  if(text_selected)
  {
    start_text->getText()->setFillColor(sf::Color(255,255,255,alphaDefault_text));
    quit_text->getText()->setFillColor(sf::Color(255,255,255,alphaNotSelected_text));
  }
  else
  {
    start_text->getText()->setFillColor(sf::Color(255,255,255,alphaNotSelected_text));
    quit_text->getText()->setFillColor(sf::Color(255,255,255,alphaDefault_text));
  }

}

void Menu::keyPressed(sf::Event event)
{
  if(inMianMenu)
  {
    if((event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up) ||
        (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down))
    {
      text_selected = !text_selected;
    }

    if(event.key.code == sf::Keyboard::Enter)
    {
      if(text_selected)
      {
        enter_start = true;
      }
      else
      {
        enter_quit = true;
      }
    }
  }
}

void Menu::keyReleased(sf::Event event)
{
  if(!inMianMenu)
  {
    if(event.KeyPressed)
    {
      inMianMenu = true;
    }
  }
}

bool Menu::getStartBool()
{
  return enter_start;
}

void Menu::setStartBool(bool boolean)
{
  enter_start = boolean;
}

bool Menu::getQuitBool()
{
  return enter_quit;
}

void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.setView(*view->getCamera());
  target.draw(*title->getText());
  if(!inMianMenu)
  {
    target.draw(*prompt_text_start->getText());
  }
  else
  {
    target.draw(*start_text->getText());
    target.draw(*quit_text->getText());
  }
}