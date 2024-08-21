#include "Entidades/Projetil.hpp"

const char *PROJETIL_PATH = "./assets/images/bullet.png";

Projetil::Projetil(int px, int py, int direcao) : Entidade(px, py, tipoDeEntidade::PROJETIL),
                                                  visual(PROJETIL_PATH, true), direcao(direcao)
{
  visual.setPosition(px, py);
  visual.setTextureRect(sf::IntRect(0, 0, 80, 64 * 2));
  visual.setScale(3, 3);
}

Projetil::~Projetil()
{
}

void Projetil::desenhar()
{
  visual.desenhar();
}

void Projetil::executar()
{
}

sf::Vector2f Projetil::getCenter()
{
  return visual.getCenter();
}

sf::FloatRect Projetil::getSize()
{
  return visual.getSize();
}

void Projetil::lidarColisao(sf::Vector2f intersecao, Entidade *other) {}