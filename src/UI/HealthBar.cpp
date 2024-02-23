//
// Created by OscarNg on 2023/12/4.
//

#include "HealthBar.h"
HealthBar::HealthBar()
{
  charIconBox = std::make_unique<GameObject>();
  charIcon = std::make_unique<GameObject>();
  hpBox     = std::make_unique<GameObject>();
  healthBar = std::make_unique<GameObject>();

  charIconBox_texture = std::make_unique<sf::Texture>();
  charIcon_texture = std::make_unique<sf::Texture>();
  hpBox_texture = std::make_unique<sf::Texture>();
  healthBar_texture = std::make_unique<sf::Texture>();
}

void HealthBar::init(int fullHealth,  UserData::characterSkin player_skin, float scale)
{
  fullHp = fullHealth;

  std::cout << fullHp << std::endl;
  if(!charIconBox_texture->loadFromFile("Data/Images/UI/GUI char icon box.png"))
  {
    std::cout << "Sprite texture loading error" << std::endl;
  }

  charIconBox->initSprite(*charIconBox_texture);
  charIconBox->GetSprite()->setScale(scale, scale);

  switch (player_skin)
  {
    case UserData::DAVID:
      charIcon_texture->loadFromFile("Data/Images/character/PNGS/Character singlesprite/davidmartinez.png");
      break ;
    case UserData::LUCY:
      charIcon_texture->loadFromFile("Data/Images/character/PNGS/Character singlesprite/lucy.png");
      break ;
    case UserData::REBECCA:
      charIcon_texture->loadFromFile("Data/Images/character/PNGS/Character singlesprite/rebecca.png");
      break ;
  }

  charIcon->initSprite(*charIcon_texture);
  charIcon->GetSprite()->setScale(scale /2, scale /2);

  if(!hpBox_texture->loadFromFile("Data/Images/UI/GUI health bar box.png"))
  {
    std::cout << "Sprite texture loading error" << std::endl;
  }

  hpBox->initSprite(*hpBox_texture);
  hpBox->GetSprite()->setScale(scale, scale);

  if(!healthBar_texture->loadFromFile("Data/Images/UI/GUI health bar.png"))
  {
    std::cout << "Sprite texture loading error" << std::endl;
  }

  healthBar->initSprite(*healthBar_texture);
  healthBar->GetSprite()->setScale(scale, scale);
}

void HealthBar::setPostion(Camera& camera)
{
  charIconBox->GetSprite()->setPosition(camera.getCamera()->getCenter().x - camera.getCamera()->getSize().x/2 + 10,
                                        camera.getCamera()->getCenter().y - camera.getCamera()->getSize().y/2+ 10);

  charIcon->GetSprite()->setPosition(charIconBox->GetSprite()->getPosition().x + charIconBox->GetSprite()->getGlobalBounds().width /2 - charIcon->GetSprite()->getGlobalBounds().width /2,
                                     charIconBox->GetSprite()->getPosition().y + charIconBox->GetSprite()->getGlobalBounds().height /2 - charIcon->GetSprite()->getGlobalBounds().height /2);

  hpBox->GetSprite()->setPosition(charIconBox->GetSprite()->getPosition().x + charIconBox->GetSprite()->getGlobalBounds().width, charIconBox->GetSprite()->getPosition().y);

  healthBar->GetSprite()->setPosition(hpBox->GetSprite()->getPosition().x, hpBox->GetSprite()->getPosition().y + hpBox->GetSprite()->getGlobalBounds().height *2/5);
}

void HealthBar::resetHealthBar(float scale)
{
  healthBar->GetSprite()->setScale(scale, scale);
}

void HealthBar::healthchanged(int newHealth)
{
  float health = newHealth;
  float scale = health / fullHp;
  healthBar->GetSprite()->setScale(healthBar->GetSprite()->getScale().x * scale,healthBar->GetSprite()->getScale().y);
  std::cout << healthBar->GetSprite()->getScale().x << std::endl;
}

void HealthBar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(*charIconBox->GetSprite());
  target.draw(*charIcon->GetSprite());
  target.draw(*hpBox->GetSprite());
  target.draw(*healthBar->GetSprite());
}