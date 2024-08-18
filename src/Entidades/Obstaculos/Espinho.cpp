#include "Entidades/Obstaculos/Espinho.hpp"

const char *ESPINHO_PATH = "./assets/tiles/espinho.png";

Espinho::Espinho(int px, int py) : Obstaculo(px, py, tipoDeEntidade::ESPINHO), visual(ESPINHO_PATH)
{
  visual.setPosition(px, py);
  visual.setTextureRect(sf::IntRect(0, 0, 16, 16));
  visual.setScale(3, 3);
}

Espinho::~Espinho()
{
}

void Espinho::desenhar()
{
  visual.desenhar();
}

void Espinho::executar()
{
}

sf::Vector2f Espinho::getCenter()
{
  return visual.getCenter();
}

sf::FloatRect Espinho::getSize()
{
  return visual.getSize();
}

void Espinho::lidarColisao(sf::Vector2f intersecao, Entidade *other) {}