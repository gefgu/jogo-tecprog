#include "Entidades/Plataforma.hpp"

const char *PLATAFORMA_PATH = "./assets/tiles/plataforma_2.png";

Plataforma::Plataforma(int px, int py) : Entidade(px, py, tipoDeEntidade::PLATAFORMA),
                                         visual(PLATAFORMA_PATH, true)
{
  visual.setPosition(px, py);
  visual.setTextureRect(sf::IntRect(0, 0, 80, 64 * 2));
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

Json::Value Plataforma::gravar()
{
  Json::Value entityJson;

  entityJson["type"] = getTipo();
  entityJson["x"] = getPosition().x;
  entityJson["y"] = getPosition().y;
  return entityJson;
}