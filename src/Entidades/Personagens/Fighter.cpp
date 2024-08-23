#include "Entidades/Personagens/Fighter.hpp"
#include "Fases/Fase.hpp" // Full definition

const float SCALING_FACTOR = 3;

const float WALK_VELOCIDADE_MAXIMA = 3;
const float RUN_VELOCIDADE_MAXIMA = 6;

const float VELOCIDADE_CORRIDA = 1.5f; // Velocidade de corrida (em unidades por

const float HURT_ANIMATION_TIME = 150.0f;
const float DEATH_ANIMATION_TIME = 750.0f;

using namespace std;

Fighter::Fighter(int px, int py, int vidas) : Inimigo(px, py, vidas, tipoDeEntidade::FIGHTER), dano_soco(1), tempoContato(0.0f)
{
  animacao.addTrilha("idle", new TrilhaAnimacao(6, 15, 128, 128, 3.0, 3.0, "./assets/Gangsters_2/Idle.png"));
  animacao.addTrilha("running", new TrilhaAnimacao(9, 10, 128, 128, 3.0, 3.0, "./assets/Gangsters_2/Run.png"));
  animacao.addTrilha("walking", new TrilhaAnimacao(9, 10, 128, 128, 3.0, 3.0, "./assets/Gangsters_2/Walk.png"));
  animacao.addTrilha("attack", new TrilhaAnimacao(5, 10, 128, 128, 3.0, 3.0, "./assets/Gangsters_2/Attack_1.png"));
  animacao.addTrilha("jump", new TrilhaAnimacao(10, 9, 128, 128, 3.0, 3.0, "./assets/Gangsters_2/Jump.png"));
  animacao.addTrilha("hurt", new TrilhaAnimacao(3, 7, 128, 128, 3.0, 3.0, "./assets/Gangsters_2/Hurt.png"));
  animacao.addTrilha("dead", new TrilhaAnimacao(4, 20, 128, 128, 3.0, 3.0, "./assets/Gangsters_2/Dead.png", false));
  animacao.setPosition(px, py);
  animacao.setScale(SCALING_FACTOR, SCALING_FACTOR);
  setColisionBoxSize(sf::Vector2f(30 * SCALING_FACTOR, 128 * SCALING_FACTOR));
  visao.setPosition(px, py);
  setAnimationState();
}

Fighter::~Fighter() {}

void Fighter::perseguir()
{
  Jogador *pJ = visao.getJogador();
  if (pJ == NULL)
    return;
  newState = IDLE;
  mudouDirecao = false;
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
  }
  else if (abs(distance) > 30 * 3)
  {
    newState = WALK;
  }
  else
  {
    atacar();
    newState = ATTACK;
  }
}

void Fighter::executar()
{
  if (!morto)
  {
    float elapsed_time = pGG->getElapsedTime();
    noChao = tempoDesdeUltimoPiso <= COOLDOWN_PISO;
    newState = IDLE;
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
    if (!noChao)
    {
      newState = JUMP;
    }

    tempoDesdeUltimoPiso += elapsed_time;
    tempoDesdeUltimoDano += elapsed_time;

    if (state == WALK)
    {
      velocidadeX += (elapsed_time / 50.0f); // taking up speed
      velocidadeX = min(velocidadeX, WALK_VELOCIDADE_MAXIMA);
    }
    else if (state == RUN)
    {
      velocidadeX += (elapsed_time / 100.0f); // taking up speed
      velocidadeX = min(velocidadeX, RUN_VELOCIDADE_MAXIMA);
    }
    else
    {
      velocidadeX = 0;
    }

    x += direcao * velocidadeX;
    y += velocidadeY;

    if (getVidas() <= 0)
    {
      tempoDesdeMorte += elapsed_time;
    }

    if (y > 2000)
    {
      ativo = false;
      morto = true;
      velocidadeX = 0;
      velocidadeY = 0;
    }

    if (tempoDesdeUltimoDano < HURT_ANIMATION_TIME)
    {
      newState = HURT;
    }

    if (tempoDesdeMorte > 0.0f && tempoDesdeMorte <= DEATH_ANIMATION_TIME)
    {
      newState = DEAD;
    }
    else if (tempoDesdeMorte > DEATH_ANIMATION_TIME)
    {
      morto = true;
      pFase->alteraPontos(200);
    }

    if (!morto && (mudouDirecao || newState != state))
    {
      state = newState;
      setAnimationState();
    }
  }

  animacao.setPosition(x, y);
  colisionBox.setPosition(x, y);
  visao.setPosition(x, y);
  animacao.update();
  desenhar();
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