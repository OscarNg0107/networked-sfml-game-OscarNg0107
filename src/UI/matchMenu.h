//
// Created by st2-ng on 29/11/2023.
//

#ifndef SFMLGAME_MATCHMENU_H
#define SFMLGAME_MATCHMENU_H

#include "../Camera/Camera.h"
#include "../Network/UserData.h"
#include "Text.h"
#include <SFML/Graphics.hpp>

class matchMenu
{
  enum menustate
  {
    MENU,
    FINDMATCH,
    OPENMATCH,
    MATCHINFO,
  };
 public:
  void init();
  void update();
  int keyPressed(sf::Event event,Camera& camera, const sf::Font& font);


 private:
  std::unique_ptr<sf::RectangleShape> panel_MENU;
  std::unique_ptr<sf::RectangleShape> panel_join_MENU;
  std::unique_ptr<sf::RectangleShape> panel_Open_MENU;
  std::unique_ptr<Text> text_title_MENU;
  std::unique_ptr<Text> text_join_MENU;
  std::unique_ptr<Text> text_Open_MENU;


  std::vector<std::unique_ptr<sf::RectangleShape>> matches_found;
  std::unique_ptr<Text> text_title_FINDMATCH;


  menustate menuState;

  bool isOpened;
};

#endif // SFMLGAME_MATCHMENU_H
