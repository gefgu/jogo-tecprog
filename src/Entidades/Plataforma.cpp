#include "Entidades/Plataforma.hpp"

const char *PLATAFORMA_PATH = "./assets/tiles/plataforma.png";

Plataforma::Plataforma(int px, int py) : Entidade(tipoDeEntidade::PLATAFORMA), visual(PLATAFORMA_PATH, true)
{
  visual.setPosition(px, py);
  visual.setTextureRect(sf::IntRect(0, 0, 32, 16));
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