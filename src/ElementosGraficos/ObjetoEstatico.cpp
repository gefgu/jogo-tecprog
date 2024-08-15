#include "ElementosGraficos/ObjetoEstatico.hpp"

ObjetoEstatico::ObjetoEstatico(const char *path)
{
  sf::Texture *tex = Gerenciador_Grafico::getInstance().carregaTextura(path);
  sprite.setTexture(*tex);
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
  Gerenciador_Grafico::getInstance().drawSprite(sprite);
}

void ObjetoEstatico::setTextureRect(sf::IntRect rec)
{
  sprite.setTextureRect(rect);
}