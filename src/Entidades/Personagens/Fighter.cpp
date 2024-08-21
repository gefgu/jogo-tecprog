#include "Entidades/Personagens/Fighter.hpp"

const float SCALING_FACTOR = 3;

Fighter::Fighter(int px, int py, int vidas) : Inimigo(px, py, vidas), dano_soco(1)
{
  animacao.addTrilha("idle", new TrilhaAnimacao(6, 15, 128, 128, 3.0, 3.0, "./assets/Gangsters_2/Idle.png"));
  animacao.addTrilha("running", new TrilhaAnimacao(10, 10, 128, 128, 3.0, 3.0, "./assets/Gangsters_2/Run.png"));
  animacao.addTrilha("walking", new TrilhaAnimacao(10, 10, 128, 128, 3.0, 3.0, "./assets/Gangsters_2/Walk.png"));
  animacao.addTrilha("jump", new TrilhaAnimacao(10, 10, 128, 128, 3.0, 3.0, "./assets/Gangsters_2/Jump.png"));
  animacao.setPosition(px, py);
  animacao.setScale(SCALING_FACTOR, SCALING_FACTOR);
  setColisionBoxSize(sf::Vector2f(40 * SCALING_FACTOR, 128 * SCALING_FACTOR));
  setAnimationState();
}

Fighter::~Fighter() {}

void Fighter::executar()
{
  // aplicarGravidade();
  animacao.setPosition(x, y);
  colisionBox.setPosition(x, y);
  animacao.update();
  desenhar();
}

void Fighter::atacar() {}

void Fighter::lidarColisao(sf::Vector2f intersecao, Entidade *other) {}