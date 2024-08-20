#include "ElementosGraficos/ObjetoEstatico.hpp"

ObjetoEstatico::ObjetoEstatico(const char *path, bool repeat)
{
  sf::Texture *tex = pGG->carregaTextura(path);
  sf::IntRect textureRect(0, 0, tex->getSize().x, tex->getSize().y);
  tex->setRepeated(repeat);
  sprite.setTexture(*tex);
  sprite.setTextureRect(textureRect);
  sprite.setOrigin(tex->getSize().x / 2.f, tex->getSize().y / 2.f); // Define a origem no centro da sprite
}

ObjetoEstatico::~ObjetoEstatico() {}

void ObjetoEstatico::setPosition(int px, int py)
{
  sprite.setPosition(px, py);
}

void ObjetoEstatico::setScale(float sx, float sy)
{
  sprite.setScale(sx, sy);
}

void ObjetoEstatico::desenhar()
{
  pGG->draw(sprite);
}

void ObjetoEstatico::setTextureRect(sf::IntRect rec)
{
  sprite.setTextureRect(rec);
}

sf::Vector2f ObjetoEstatico::getCenter()
{
  sf::FloatRect size = getSize();
  return sf::Vector2f(size.left + size.width / 2.0f, size.top + size.height / 2.0f);
}

sf::FloatRect ObjetoEstatico::getSize()
{
  return sprite.getGlobalBounds();
}

void ObjetoEstatico::executar() {}