#include "Entidades/Obstaculos/Plataforma.hpp"

const char *PLATAFORMA_PATH = "./assets/tiles/plataforma_2.png";

Plataforma::Plataforma(int px, int py) : Obstaculo(px, py, PLATAFORMA_PATH, tipoDeEntidade::PLATAFORMA)
{
  visual.setPosition(px, py);
  visual.setTextureRect(sf::IntRect(0, 0, 80, 64 * 8));
  visual.setScale(3, 3);
}

Plataforma::~Plataforma()
{
}

void Plataforma::executar()
{
}

void Plataforma::lidarColisao(sf::Vector2f intersecao, Entidade *other) {}

Json::Value Plataforma::gravar()
{
  Json::Value entityJson;

  entityJson["type"] = getTipo();
  entityJson["x"] = getPosition().x;
  entityJson["y"] = getPosition().y;
  return entityJson;
}