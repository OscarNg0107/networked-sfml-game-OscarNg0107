//
// Created by OscarNg on 2023/10/13.
//

#include "Text.h"

Text::Text()
{
  text = std::make_unique<sf::Text>();
}

Text::Text(std::string string, const sf::Font& font, unsigned int size) : Text()
{
  text->setString(string);
  text->setFont(font);
  text->setCharacterSize(size);
}

void Text::init(const std::string& string, const sf::Font& font, unsigned int size)
{
  text->setString(string);
  text->setFont(font);
  text->setCharacterSize(size);
}

std::unique_ptr<sf::Text>& Text::getText()
{
  return text;
}

void Text::setVisible(bool boolean)
{
  isVisible = boolean;
}

bool Text::getVisisble()
{
  return isVisible;
}

void Text::changeAlphaV(int alphaValue)
{
  int alpha = text->getFillColor().a;
  alpha += alphaValue;
  text->setFillColor(sf::Color(text->getFillColor().r,text->getFillColor().g,text->getFillColor().b,alpha));
}