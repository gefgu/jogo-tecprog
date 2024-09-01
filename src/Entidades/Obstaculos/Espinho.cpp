#include "Entidades/Obstaculos/Espinho.hpp"

const char *ESPINHO_PATH = "./assets/tiles/espinho.png";

Espinho::Espinho(int px, int py) : Obstaculo(px, py, ESPINHO_PATH, tipoDeEntidade::ESPINHO), dano(1)
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

Json::Value Espinho::gravar()
{
  Json::Value entityJson;

  entityJson["type"] = getTipo();
  entityJson["x"] = getPosition().x;
  entityJson["y"] = getPosition().y;
  return entityJson;
}

int Espinho::getDano()
{
  return dano;
}