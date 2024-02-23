//
// Created by OscarNg on 2023/10/27.
//

#ifndef SFMLGAME_CHATROOM_H
#define SFMLGAME_CHATROOM_H

#include "../Camera/Camera.h"
#include "../Network/Client.h"
#include "Text.h"
#include <SFML/Graphics.hpp>

class Chatroom : public sf::Drawable
{
 public:
  Chatroom();
  ~Chatroom() = default;
  void init(const sf::Font& font);
  void update(Client& client, Camera& camera);
  void KeyPressed(sf::Event event, std::string& username, Client& client);
  void KeyReleased(sf::Event event, Camera& camera);
  void TextEntered(sf::Event event);
  void mouseWheelMoved(sf::Event event);
  bool getIsOpened();

  void setChatPosition();

 private:
  virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const ;
  sf::RectangleShape chatPanel;
  std::vector<std::unique_ptr<Text>> text_logs;

  std::string user_input;
  std::unique_ptr<Text> user_input_text= nullptr;
  std::unique_ptr<Text> typing= nullptr;
  int typingBlinkTimer = 0;
  bool blink = true;
  bool istyping = false;
  sf::Font text_font;
  sf::Glyph line_length;
  float texts_height;

  bool isOpened = false;
};

#endif // SFMLGAME_CHATROOM_H
