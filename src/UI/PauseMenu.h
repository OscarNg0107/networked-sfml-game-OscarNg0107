//
// Created by OscarNg on 2023/11/26.
//

#ifndef SFMLGAME_PAUSEMENU_H
#define SFMLGAME_PAUSEMENU_H
#include "../Camera/Camera.h"
#include "Text.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class PauseMenu : public sf::Drawable
{
 public:
  PauseMenu();
  ~PauseMenu() = default;
  void init(int NumOfElements, const sf::Font& font, unsigned int textsize);
  void setPosition(Camera& camera, const sf::Font& font);
  void update();
  int keyPressed(sf::Event event,Camera& camera, const sf::Font& font);
  void addOptions(std::string option_text, const sf::Font& font, unsigned int size);
  bool getIsOpened();
  void setIsOpened(bool boolean);

 private:
  virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

  std::unique_ptr<Text> pauseTitle = nullptr;
  std::unique_ptr<sf::RectangleShape> optionPanel = nullptr;
  std::unique_ptr<sf::RectangleShape> bgPanel = nullptr;
  std::vector<std::unique_ptr<Text>> option_lists;

  int listSize;

  int option_selected = 0;
  bool isOpened = false;


};

#endif // SFMLGAME_PAUSEMENU_H
