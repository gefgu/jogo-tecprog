#include "Entidades/Personagens/Fighter.hpp"

const float SCALING_FACTOR = 3;

const float VELOCIDADE_CORRIDA = 1.5f; // Velocidade de corrida (em unidades por

using namespace std;

Fighter::Fighter(int px, int py, int vidas) : Inimigo(px, py, vidas, tipoDeEntidade::FIGHTER), dano_soco(1), tempoContato(0.0f)
{
  animacao.addTrilha("idle", new TrilhaAnimacao(6, 15, 128, 128, 3.0, 3.0, "./assets/Gangsters_2/Idle.png"));
  animacao.addTrilha("running", new TrilhaAnimacao(9, 10, 128, 128, 3.0, 3.0, "./assets/Gangsters_2/Run.png"));
  animacao.addTrilha("walking", new TrilhaAnimacao(9, 10, 128, 128, 3.0, 3.0, "./assets/Gangsters_2/Walk.png"));
  animacao.addTrilha("attack", new TrilhaAnimacao(5, 10, 128, 128, 3.0, 3.0, "./assets/Gangsters_2/Attack_1.png"));
  animacao.addTrilha("jump", new TrilhaAnimacao(10, 10, 128, 128, 3.0, 3.0, "./assets/Gangsters_2/Jump.png"));
  animacao.setPosition(px, py);
  animacao.setScale(SCALING_FACTOR, SCALING_FACTOR);
  setColisionBoxSize(sf::Vector2f(40 * SCALING_FACTOR, 128 * SCALING_FACTOR));
  visao.setPosition(px, py);
  setAnimationState();
}

Fighter::~Fighter() {}

void Fighter::perseguir()
{
  Jogador *pJ = visao.getJogador();
  if (pJ == NULL)
    return;
  estadoPersonagem newState = IDLE;
  bool mudouDirecao = false;
  float elapsed_time = pGG->getElapsedTime();

  int distance = pJ->getCenter().x - getCenter().x;

  if (distance < 0)
  {
    mudouDirecao = direcao == 1;
    direcao = -1;
  }
  else
  {
    mudouDirecao = direcao == -1;
    direcao = 1;
  }

  if (abs(distance) > 200)
  {
    newState = RUN;
    x += direcao * velocidadeX * VELOCIDADE_CORRIDA * (elapsed_time / 100.0);
  }
  else if (abs(distance) > 50)
  {
    newState = WALK;
    x += direcao * velocidadeX * (elapsed_time / 100.0);
  }
  else
  {
    atacar();
    newState = ATTACK;
  }

  if (mudouDirecao || newState != state)
  {
    state = newState;
    setAnimationState();
  }
}

void Fighter::executar()
{
  float elapsed_time = pGG->getElapsedTime();
  aplicarGravidade();
  if (state == ATTACK)
  {
    tempoContato += elapsed_time;
  }
  else
  {
    tempoContato = 0;
  }
  if (visao.getJogador())
  {
    perseguir();
  }

  tempoDesdeUltimoPiso += elapsed_time;

  animacao.setPosition(x, y);
  colisionBox.setPosition(x, y);
  visao.setPosition(x, y);
  animacao.update();
  desenhar();
  visao.desenhar();
}

void Fighter::atacar()
{
  Jogador *pJ = visao.getJogador();
  if (tempoContato > 500.f)
  {
    if (pJ)
    {
      pJ->recebeDano(dano_soco);
    }
    tempoContato = 0;
  }
}

void Fighter::lidarColisao(sf::Vector2f intersecao, Entidade *other)
{
  if (other->getTipo() == tipoDeEntidade::PLATAFORMA)
  {
    if (intersecao.y > 0)
    {
      y -= intersecao.y - 1;
      tempoDesdeUltimoPiso = 0.0f;
      velocidadeY = 0;
    }
  }
}