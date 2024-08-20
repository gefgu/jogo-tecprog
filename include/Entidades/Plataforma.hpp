#pragma once

#include <SFML/Graphics.hpp>
#include "Entidades/Entidade.hpp"
#include "ElementosGraficos/ObjetoEstatico.hpp"

const int PLATAFORMA_WIDTH = 80;
const int PLATAFORMA_HEIGHT = 64 * 2;
class Plataforma : public Entidade
{
private:
  ObjetoEstatico visual;

public:
  Plataforma(int px, int py); // posição e escala não mudam
  ~Plataforma();
  void desenhar();
  void executar();
  sf::Vector2f getCenter();
  sf::FloatRect getSize();
  void lidarColisao(sf::Vector2f intersecao, Entidade *other);
};