#include "Entidades/Plataforma.hpp"

const char *PLATAFORMA_PATH = "./assets/tiles/Tiles.png";

Plataforma::Plataforma(int px, int py) : visual(PLATAFORMA_PATH)
{
  visual.setPosition(px, py);
  visual.setTextureRect(sf::IntRect(64, 112, 22, 16));
  visual.setScale(3, 3);
}

Plataforma::~Plataforma()
{
}

void Plataforma::desenhar()
{
  visual.desenhar();
}

void Plataforma::executar()
{
}

sf::Vector2f Plataforma::getCenter()
{
  return visual.getCenter();
}

sf::FloatRect Plataforma::getSize()
{
  return visual.getSize();
}

void Plataforma::lidarColisao(sf::Vector2f intersecao, Entidade *other) {}