//
// Created by OscarNg on 2023/10/13.
//
#include "../Camera/Camera.h"
#include "../UI/Text.h"
#ifndef SFMLGAME_MENU_H
#define SFMLGAME_MENU_H

class Menu : public sf::Drawable
{
 public:
  Menu();
  ~Menu() = default;
  void init( const sf::Font& font , unsigned int windowSizeX, unsigned int windowSizeY);
  void update();
  void keyPressed(sf::Event event);
  void keyReleased(sf::Event event);
  bool getStartBool();
  void setStartBool(bool boolean);
  bool getQuitBool();


 private:
  virtual void draw(sf::RenderTarget &target, sf::RenderStates states)const;


  bool inMianMenu = false;

  bool text_selected = true;
  bool enter_quit = false;
  bool enter_start = false;

  int alphaDefault_text = 255;
  int alphaNotSelected_text = 125;

  unsigned int alphafading_text = 255;
  int fadingvalue = -2;

  std::unique_ptr<Text> title = nullptr;
  std::unique_ptr<Text> prompt_text_start = nullptr;
  std::unique_ptr<Text> start_text = nullptr;
  std::unique_ptr<Text> quit_text = nullptr;
  std::unique_ptr<Camera> view = nullptr;

};

#endif // SFMLGAME_MENU_H
