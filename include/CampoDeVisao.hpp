#pragma once

#include "Ente.hpp"
#include "Entidades/Personagens/Jogador.hpp"

class CampoDeVisao : public Ente
{
private:
  Jogador *pJogador;
  sf::RectangleShape visao;

public:
  CampoDeVisao();
  ~CampoDeVisao();
  sf::Vector2f getCenter();
  sf::FloatRect getSize();
  void setPosition(int px, int py);
  Jogador *getJogador();
  void lidarColisao(sf::Vector2f intersecao, Entidade *other);
};
