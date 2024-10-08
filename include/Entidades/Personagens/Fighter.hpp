#pragma once

#include "Inimigo.hpp"
#include "Jogador.hpp"

const int FIGHTER_HEIGHT = 128 * 3;

class Fighter : public Inimigo
{
private:
  float dano_soco;
  float tempoContato;

public:
  Fighter(int px, int py, int vidas);
  ~Fighter();
  void executar();
  void atacar();
  void perseguir();
  void danificar(Jogador *pJ);
  void lidarColisao(sf::Vector2f intersecao, Entidade *other);
  Json::Value gravar();
};
