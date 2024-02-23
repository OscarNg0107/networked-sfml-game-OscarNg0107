//
// Created by OscarNg on 2023/10/17.
//

#include "PlayerInit.h"
#include <iostream>

PlayerInit::PlayerInit()
{
  askUsername = std::make_unique<Text>();
  inputUsername = std::make_unique<Text>();
  selectSkinText = std::make_unique<Text>();
  prompt_enter = std::make_unique<Text>();
  charIcon_david = std::make_shared<GameObject>();
  warningNoName  =  std::make_unique<Text>();
}

void PlayerInit::init(const sf::Font& font, unsigned int windowSizeX, unsigned int windowSizeY)
{
  askUsername->init("Username", font, 50);
  askUsername->getText()->setPosition(windowSizeX/2 - askUsername->getText()->getGlobalBounds().width /2, windowSizeY / 3);
  askUsername->getText()->setFillColor(sf::Color(255,255,255,255));

  textField.setSize(sf::Vector2f (300,40));
  textField.setPosition(windowSizeX /2 - textField.getGlobalBounds().width /2, windowSizeY / 2.5 + textField.getGlobalBounds().height);
  textField.setFillColor(sf::Color(200,200,200,125));

  inputUsername->init("username", font, 30);
  inputUsername->getText()->setFillColor(sf::Color(255,255,255,125));
  inputUsername->getText()->setPosition(textField.getPosition().x +10, textField.getPosition().y);

  selectSkinText->init("Choose your character" , font , 30);
  selectSkinText->getText()->setPosition(windowSizeX /2 - selectSkinText->getText()->getGlobalBounds().width /2, windowSizeY / 2);
  selectSkinText->getText()->setFillColor(sf::Color(255,255,255,255));

  prompt_enter->init("Press [Enter] to start", font , 40);
  prompt_enter->getText()->setPosition(windowSizeX - prompt_enter->getText()->getGlobalBounds().width * 1.5,
                                      windowSizeY - prompt_enter->getText()->getGlobalBounds().height * 1.5);
  prompt_enter->getText()->setFillColor(sf::Color(255,255,255,200));

  warningNoName->init("WARNING: NAME INVALID", font, 20);
  warningNoName->getText()->setFillColor(sf::Color(255,0,0,200));
  warningNoName->getText()->setPosition(windowSizeX /2 - warningNoName->getText()->getGlobalBounds().width /2, windowSizeY / 2.1);



  david_texture = std::make_unique<sf::Texture>();
  if(!david_texture->loadFromFile("Data/Images/character/PNGS/Character singlesprite/davidmartinez.png"))
  {
    std::cout << "Sprite texture loading error";
  }
  charIcon_david->initSprite(*david_texture);
  charIcon_david->GetSprite()->setScale(7.0f,7.0f);

  charIcon_lucy = std::make_unique<GameObject>();
  lucy_texture = std::make_unique<sf::Texture>();
  if(!lucy_texture->loadFromFile("Data/Images/character/PNGS/Character singlesprite/lucy.png"))
  {
    std::cout << "Sprite texture loading error";
  }
  charIcon_lucy->initSprite(*lucy_texture);
  charIcon_lucy->GetSprite()->setScale(7.0f,7.0f);

  charIcon_rebecca = std::make_unique<GameObject>();
  rebecca_texture = std::make_unique<sf::Texture>();
  if(!rebecca_texture->loadFromFile("Data/Images/character/PNGS/Character singlesprite/rebecca.png"))
  {
    std::cout << "Sprite texture loading error";
  }
  charIcon_rebecca->initSprite(*rebecca_texture);
  charIcon_rebecca->GetSprite()->setScale(7.0f,7.0f);

  charIcon.push_back(charIcon_david);
  charIcon.push_back(charIcon_lucy);
  charIcon.push_back(charIcon_rebecca);

  for(int i = 0; i < charIcon.size(); ++i)
  {
    charIcon[i]->GetSprite()->setPosition(windowSizeX /4 + charIcon[i]->GetSprite()->getGlobalBounds().width * i,
                            windowSizeY / 1.7);
  }

  if(!ui_selected_texture.loadFromFile("Data/Images/UI/selected.png"))
  {
    std::cout << "UI texture load error";
  }
  ui_selected.setTexture(ui_selected_texture);
  ui_selected_texture_rect = sf::IntRect (0, 0,ui_selected_texture.getSize().x/4, ui_selected_texture.getSize().y);
  ui_selected.setTextureRect(ui_selected_texture_rect);
  ui_selected.setScale(7.0f,7.0f);
  ui_selected.setPosition(charIcon[0]->GetSprite()->getPosition());
}

void PlayerInit::update(unsigned int windowSizeX, unsigned int windowSizeY)
{
  if(userIsEntering)
  {
    inputUsername->getText()->setString(username);
  }
  inputUsername->getText()->setPosition( inputUsername->getText()->getPosition().x, inputUsername->getText()->getPosition().y);

  switch (skin_selected)
  {
    case UserData::DAVID:
      ui_selected.setPosition(charIcon[0]->GetSprite()->getPosition());
      break ;
    case UserData::LUCY:
      ui_selected.setPosition(charIcon[1]->GetSprite()->getPosition());
      break ;
    case UserData::REBECCA:
      ui_selected.setPosition(charIcon[2]->GetSprite()->getPosition());
      break ;
  }
}

void PlayerInit::mouseClicked(sf::Event event, float clickX, float clickY)
{
  if(event.mouseButton.button == sf::Mouse::Left)
  {
    for(int i = 0; i < charIcon.size(); ++i)
    {
      if (charIcon[i]->GetSprite()->getGlobalBounds().contains(clickX, clickY))
      {
        switch (i)
        {
          case 0:
            skin_selected = UserData::DAVID;
            break ;
          case 1:
            skin_selected = UserData::LUCY;
            break ;
          case 2:
            skin_selected = UserData::REBECCA;
            break ;
        }
      }
    }
  }
}

void PlayerInit::TextEntered(sf::Event event)
{
  userIsEntering = true;
  if(event.text.unicode < 128 && event.text.unicode != 8 && event.text.unicode != 13 && event.text.unicode != 27 && event.text.unicode != 9&& event.text.unicode != 32)
  {
    if(username.length() <= 12)
    {
      username += event.text.unicode;
    }
  }
}

void PlayerInit::keyPressed(sf::Event event)
{
  if(event.key.code == sf::Keyboard::BackSpace)
  {
    if(username.length() > 0)
    {
      username.pop_back();
    }
  }

  if(event.key.code == sf::Keyboard::Enter)
  {
    if(username.length() > 0)
    {
      pressedEntered = true;
    }
    else
    {
      nameInvalid = true;
    }
  }
}

std::string PlayerInit::getUsername()
{
  return username;
}

bool PlayerInit::getPressEnterBool()
{
  return pressedEntered;
}

void PlayerInit::setPressEnterBool(bool boolean)
{
  pressedEntered = boolean;
}

UserData::characterSkin PlayerInit::getCharSkinEnum()
{
  return skin_selected;
}

void PlayerInit::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(*askUsername->getText());
  target.draw(textField);
  target.draw(*inputUsername->getText());
  target.draw(*selectSkinText->getText());
  target.draw(*prompt_enter->getText());


  if(nameInvalid)
  {
    target.draw(*warningNoName->getText());
  }
  for(int i = 0; i < charIcon.size(); ++i)
  {
    target.draw(*charIcon[i]->GetSprite());
  }
  target.draw(ui_selected);
}