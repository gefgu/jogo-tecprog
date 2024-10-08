#include "Entidades/Personagens/Atirador.hpp"
#include "Fases/Fase.hpp" // Full definition
#include <unistd.h>

const float SCALING_FACTOR = 3;

const float COOLDOWN_TIRO = 965.0f;

const float HURT_ANIMATION_TIME = 150.0f;
const float DEATH_ANIMATION_TIME = 750.0f;
const float SHOT_ANIMATION_TIME = 1200.0f;

using namespace std;

Atirador::Atirador(int px, int py, int vidas) : Inimigo(px, py, vidas, tipoDeEntidade::ATIRADOR), dano_projetil(1), tempoDisparo(COOLDOWN_TIRO)
{
  animacao.addTrilha("idle", new TrilhaAnimacao(6, 15, 128, 128, 3.0, 3.0, "./assets/Gangsters_3/Idle.png"));
  animacao.addTrilha("running", new TrilhaAnimacao(9, 10, 128, 128, 3.0, 3.0, "./assets/Gangsters_3/Run.png"));
  animacao.addTrilha("walking", new TrilhaAnimacao(9, 10, 128, 128, 3.0, 3.0, "./assets/Gangsters_3/Walk.png"));
  animacao.addTrilha("shot", new TrilhaAnimacao(11, 10, 128, 128, 3.0, 3.0, "./assets/Gangsters_3/Shot.png"));
  animacao.addTrilha("jump", new TrilhaAnimacao(10, 10, 128, 128, 3.0, 3.0, "./assets/Gangsters_3/Jump.png"));
  animacao.addTrilha("hurt", new TrilhaAnimacao(3, 7, 128, 128, 3.0, 3.0, "./assets/Gangsters_3/Hurt.png"));
  animacao.addTrilha("dead", new TrilhaAnimacao(4, 20, 128, 128, 3.0, 3.0, "./assets/Gangsters_3/Dead.png", false));
  animacao.setPosition(px, py);
  animacao.setScale(SCALING_FACTOR, SCALING_FACTOR);
  setColisionBoxSize(sf::Vector2f(30 * SCALING_FACTOR, 128 * SCALING_FACTOR));
  visao.setPosition(px, py);
  setAnimationState();
}

Atirador::~Atirador() {}

void Atirador::olhar()
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
  if (abs(distance) < 550)
  {
    if (tempoDisparo <= SHOT_ANIMATION_TIME)
    {
      atacar();
      newState = SHOT;
    }
  }
  else
  {
    newState = IDLE;
  }
}

void Atirador::executar()
{

  if (!morto)
  {
    float elapsed_time = pGG->getElapsedTime();
    newState = IDLE;
    aplicarGravidade();
    if (state == SHOT)
    {
      tempoDisparo += elapsed_time;
    }
    else
    {
      tempoDisparo = 0;
    }
    if (visao.getJogador())
    {
      olhar();
    }

    tempoDesdeUltimoPiso += elapsed_time;
    tempoDesdeUltimoDano += elapsed_time;
    if (getVidas() <= 0)
    {
      tempoDesdeMorte += elapsed_time;
    }

    if (tempoDesdeUltimoDano < HURT_ANIMATION_TIME)
    {
      newState = HURT;
      tempoDisparo = 0;
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

void Atirador::atacar()
{
    if (tempoDisparo >= COOLDOWN_TIRO)
    {
        Jogador *pJ = visao.getJogador();
        Projetil* proj = pFase->addProjetil(x + direcao * 120, y + (getSize().height / 12), direcao, ATIRADOR);
        tempoDisparo = 0;

        if (proj->getSize().intersects(pJ->getSize()))
        {
            danificar(pJ);
        }
    }
}

void Atirador::danificar(Jogador*p)
{
    p->recebeDano(dano_projetil);
}


void Atirador::lidarColisao(sf::Vector2f intersecao, Entidade *other)
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

Json::Value Atirador::gravar()
{
  Json::Value entityJson;

  entityJson["type"] = getTipo();
  entityJson["x"] = getPosition().x;
  entityJson["y"] = getPosition().y;
  entityJson["vidas"] = getVidas();
  return entityJson;
}