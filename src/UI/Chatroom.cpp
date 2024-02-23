//
// Created by OscarNg on 2023/10/27.
//

#include "Chatroom.h"
#include <iostream>

Chatroom::Chatroom()
{
  user_input_text = std::make_unique<Text>();
  typing = std::make_unique<Text>();
}

void Chatroom::init(const sf::Font& font)
{
  text_font = font;
  texts_height = text_font.getLineSpacing(10);
  chatPanel.setSize(sf::Vector2f (250,155));
  chatPanel.setPosition(10,110);
  chatPanel.setFillColor(sf::Color(200,200,200,125));

  user_input_text->init("", font, 10);
  user_input_text->getText()->setPosition(chatPanel.getPosition().x, chatPanel.getPosition().y + chatPanel.getGlobalBounds().height);

  typing->init("|", font, 10);
  typing->getText()->setPosition(chatPanel.getPosition().x , chatPanel.getPosition().y + chatPanel.getGlobalBounds().height);
}

void Chatroom::update(Client& client, Camera& camera)
{

  chatPanel.setPosition(camera.getCamera()->getCenter().x - camera.getCamera()->getSize().x/2 +10,
                        camera.getCamera()->getCenter().y - camera.getCamera()->getSize().y/2 +110);
  setChatPosition();
  if(!client.chatText.empty())
  {
    text_logs.emplace(text_logs.begin(), std::make_unique<Text>(client.chatText, text_font, 10));
    client.chatText.clear();
  }

  if (isOpened)
  {
    typingBlinkTimer += 1;
    if(typingBlinkTimer % 50 == 0)
    {
      blink = !blink;
      typingBlinkTimer = 1;
    }
    if(blink)
    {
      typing->getText()->setFillColor(sf::Color(255,255,255,255));
    }
    else
    {
      typing->getText()->setFillColor(sf::Color(255,255,255,0));
    }

    user_input_text->getText()->setString(user_input);
    user_input_text->getText()->setPosition(chatPanel.getPosition().x, chatPanel.getPosition().y + chatPanel.getGlobalBounds().height);
    typing->getText()->setPosition(user_input_text->getText()->getPosition().x + user_input_text->getText()->getGlobalBounds().width
                                            , user_input_text->getText()->getPosition().y);
  }

  for (int i = 0; i < text_logs.size(); ++i)
  {
    if((text_logs[i]->getText()->getPosition().y + text_logs[i]->getText()->getGlobalBounds().height> chatPanel.getPosition().y + chatPanel.getGlobalBounds().height)||
        (text_logs[i]->getText()->getPosition().y < chatPanel.getPosition().y))
    {
      text_logs[i]->setVisible(false);
    }
    else
    {
      text_logs[i]->setVisible(true);
    }

    if(!isOpened)
    {
      if(text_logs[i]->textFadeCountDown.getElapsedTime().asSeconds() >=2)
      {
        if(text_logs[i]->getText()->getFillColor().a > 1)
        {
          text_logs[i]->changeAlphaV(-1);
        }
      }
      }
  }
  if(text_logs.size() > 20)
  {
    text_logs.erase(text_logs.end());
  }
}

void Chatroom::KeyPressed(sf::Event event, std::string& username, Client& client)
{
  if(isOpened)
  {
    if (event.key.code == sf::Keyboard::BackSpace)
    {
      if (user_input.length() > 0)
      {
        user_input.pop_back();
      }
    }

    if (event.key.code == sf::Keyboard::Enter && !user_input.empty())
    {
      client.sendChatMessage(username, user_input);
      std::string combinedString ="<"+  username + ">" + user_input;
      text_logs.emplace(text_logs.begin(), std::make_unique<Text>(combinedString, text_font, 10));
      user_input.clear();
    }
  }
}

void Chatroom::KeyReleased(sf::Event event, Camera& camera)
{
  if(!isOpened)
  {
    if (event.key.code == sf::Keyboard::T)
    {
      chatPanel.setPosition(camera.getCamera()->getCenter().x -camera.getCamera()->getSize().x/2 +10,
                            camera.getCamera()->getCenter().y -camera.getCamera()->getSize().y/2 +10);
      user_input_text->getText()->setPosition(chatPanel.getPosition().x, chatPanel.getPosition().y + chatPanel.getGlobalBounds().height);
      user_input.clear();
      for (int i = 0; i < text_logs.size(); ++i)
      {
        text_logs[i]->getText()->setFillColor(sf::Color(255,255,255,255));
      }
      isOpened = true;
    }
  }

  if(event.key.code == sf::Keyboard::Escape)
  {
    for (int i = 0; i < text_logs.size(); ++i)
    {
      text_logs[i]->getText()->setFillColor(sf::Color(255,255,255,0));
    }
    isOpened = false;
  }
}

void Chatroom::TextEntered(sf::Event event)
{
  if(isOpened)
  {
    if(event.text.unicode < 128 && event.text.unicode != 8 && event.text.unicode != 27 && event.text.unicode != 13)
    {
      istyping = true;
      if(user_input.length() <= 30)
      {
        user_input += event.text.unicode;
      }
    }
  }
}

void Chatroom::mouseWheelMoved(sf::Event event)
{
  if(isOpened)
  {
    //mouse wheel scroll down
    if(event.mouseWheel.delta > 0 && (text_logs.back()->getText()->getPosition().y < chatPanel.getPosition().y))
    {
      for (auto & text : text_logs)
      {
        text->getText()->setPosition(
          text->getText()->getPosition().x,
          text->getText()->getPosition().y +
            texts_height);
      }
    }
    //mouse wheel scroll up
    else if(event.mouseWheel.delta < 0&& (text_logs.front()->getText()->getPosition().y + text_logs.front()->getText()->getGlobalBounds().height
                                                > chatPanel.getPosition().y + chatPanel.getGlobalBounds().height))
    {
      for (auto & text : text_logs)
      {
        text->getText()->setPosition(
          text->getText()->getPosition().x,
          text->getText()->getPosition().y - texts_height);
      }
    }
  }
}

void Chatroom::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  if(isOpened)
  {
    target.draw(chatPanel);

    target.draw(*user_input_text->getText());
    target.draw(*typing->getText());
  }
  for(const auto & text : text_logs)
  {
    if(text->getVisisble())
    {
      target.draw(*text->getText());
    }
  }
}

bool Chatroom::getIsOpened()
{
  return isOpened;
}

void Chatroom::setChatPosition()
{
  for (int i = 0; i < text_logs.size(); ++i)
  {
    text_logs[i]->getText()->setPosition(
      chatPanel.getPosition().x, (chatPanel.getPosition().y + chatPanel.getGlobalBounds().height -texts_height) - texts_height * i);
  }
}