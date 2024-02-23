//
// Created by OscarNg on 2023/10/17.
//
#include "../GameObjects/GameObject.h"
#include "../Network/UserData.h"
#include "../UI/Text.h"
#ifndef SFMLGAME_PLAYERINIT_H
#define SFMLGAME_PLAYERINIT_H

class PlayerInit : public sf::Drawable
{
 public:
  PlayerInit();
  ~PlayerInit() = default;
  void init(const sf::Font& font, unsigned int windowSizeX, unsigned int windowSizeY);
  void update(unsigned int windowSizeX, unsigned int windowSizeY);
  void mouseClicked(sf::Event event ,float clickX, float clickY);
  void keyPressed(sf::Event event);
  void TextEntered(sf::Event event);
  bool getPressEnterBool();
  void setPressEnterBool(bool boolean);
  std::string getUsername();
  UserData::characterSkin getCharSkinEnum();

 private:
  virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

  std::unique_ptr<Text> askUsername = nullptr;
  std::unique_ptr<Text> inputUsername = nullptr;
  std::unique_ptr<Text> selectSkinText = nullptr;
  std::unique_ptr<Text> prompt_enter = nullptr;
  std::unique_ptr<Text> warningNoName   = nullptr;

  sf::RectangleShape textField;
  UserData::characterSkin skin_selected = UserData::DAVID;

  std::vector<std::shared_ptr<GameObject>> charIcon;
  std::shared_ptr<GameObject> charIcon_david = nullptr;
  std::shared_ptr<GameObject>  charIcon_lucy = nullptr;
  std::shared_ptr<GameObject>  charIcon_rebecca = nullptr;
  std::unique_ptr<sf::Texture> david_texture = nullptr;
  std::unique_ptr<sf::Texture> lucy_texture = nullptr;
  std::unique_ptr<sf::Texture> rebecca_texture= nullptr;

  sf::Sprite ui_selected;
  sf::Texture ui_selected_texture;
  sf::IntRect ui_selected_texture_rect;

  bool userIsEntering = false;
  bool pressedEntered = false;
  bool nameInvalid  = false;

  std::string username;
};

#endif // SFMLGAME_PLAYERINIT_H
