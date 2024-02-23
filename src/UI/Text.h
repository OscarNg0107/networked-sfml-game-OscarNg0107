//
// Created by OscarNg on 2023/10/13.
//
#include <SFML/Graphics.hpp>
#include <memory>
#ifndef SFMLGAME_TEXT_H
#define SFMLGAME_TEXT_H

class Text
{
 public:
  Text();
  ~Text() = default;
  Text(std::string string, const sf::Font& font, unsigned int size);
  void init(const std::string& string, const sf::Font& font, unsigned int size);
  std::unique_ptr<sf::Text>& getText();

  void setVisible(bool boolean);
  bool getVisisble();
  void changeAlphaV(int alphaValue);
  sf::Clock textFadeCountDown;
 private:
  std::unique_ptr<sf::Text> text= nullptr;
  bool isVisible = true;

};

#endif // SFMLGAME_TEXT_H
