#include "Entidades/Obstaculos/Espinho.hpp"

const char *ESPINHO_PATH = "./assets/tiles/espinho.png";

Espinho::Espinho(int px, int py) : Obstaculo(px, py, ESPINHO_PATH, tipoDeEntidade::ESPINHO)
{
  visual.setPosition(px, py);
  visual.setTextureRect(sf::IntRect(0, 0, 16, ESPINHO_HEIGHT));
  visual.setScale(3, 3);
}

Espinho::~Espinho()
{
}

void Espinho::executar()
{
}

void Espinho::lidarColisao(sf::Vector2f intersecao, Entidade *other) {}