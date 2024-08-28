#pragma once

#include <SFML/Graphics.hpp>
#include "Entidades/Entidade.hpp"
#include "ElementosGraficos/ObjetoEstatico.hpp"
#include "Entidades/Personagens/Fighter.hpp"
#include "Entidades/Personagens/Atirador.hpp"

const int PROJETIL_WIDTH = 80;
const int PROJETIL_HEIGHT = 64 * 2;
class Projetil : public Entidade
{
private:
  ObjetoEstatico visual;
  int dano;
  int direcao;
  float velocidadeY;
  tipoDeEntidade atirador;
  void aplicarGravidade();

public:
  Projetil(int px, int py, int direcao, tipoDeEntidade p); // posição e escala não mudam
  ~Projetil();
  void desenhar();
  void executar();
  sf::Vector2f getCenter();
  sf::FloatRect getSize();
  void lidarColisao(sf::Vector2f intersecao, Entidade *other);
  tipoDeEntidade getAtirador();
  Json::Value gravar();
};