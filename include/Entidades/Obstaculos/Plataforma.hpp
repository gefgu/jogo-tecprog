#pragma once

#include <SFML/Graphics.hpp>
#include "Entidades/Obstaculos/Obstaculo.hpp"
#include "Entidades/Personagens/Jogador.hpp"

const int PLATAFORMA_WIDTH = 80;
const int PLATAFORMA_HEIGHT = 64 * 8;
class Plataforma : public Obstaculo
{
public:
  Plataforma(int px, int py); // posição e escala não mudam
  ~Plataforma();
  void executar();
  void lidarColisao(sf::Vector2f intersecao, Entidade *other);
  Json::Value gravar();
};