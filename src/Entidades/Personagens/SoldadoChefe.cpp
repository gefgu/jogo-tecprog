#include "Entidades/Personagens/SoldadoChefe.hpp"
#include "Fases/Fase.hpp" // Full definition
#include <unistd.h>
#include <random>

const float SCALING_FACTOR = 3;
const float COOLDOWN_TIRO = 600.0f;
const float HURT_ANIMATION_TIME = 150.0f;
const float DEATH_ANIMATION_TIME = 750.0f;
const float SHOT_ANIMATION_TIME = 1200.0f;
const float GRENADE_COOLDOWN = 5000.0f;

using namespace std;

SoldadoChefe::SoldadoChefe(int px, int py, int vidas) : Inimigo(px, py, vidas, tipoDeEntidade::SOLDADO), dano_projetil(1), tempoDisparo(COOLDOWN_TIRO), tirosDisparados(0), maxTiros(3), tempoUltimaGranada(0.0f), numeroGranadas(1)
{
    animacao.addTrilha("idle", new TrilhaAnimacao(6, 15, 128, 128, 4.0, 4.0, "./assets/Soldier_1/Idle.png"));
    animacao.addTrilha("running", new TrilhaAnimacao(9, 10, 128, 128, 3.0, 3.0, "./assets/Soldier_1/Run.png"));
    animacao.addTrilha("walking", new TrilhaAnimacao(9, 10, 128, 128, 3.0, 3.0, "./assets/Soldier_1/Walk.png"));
    animacao.addTrilha("shot", new TrilhaAnimacao(3, 20, 128, 128, 3.0, 3.0, "./assets/Soldier_1/Shot_2.png"));
    animacao.addTrilha("hurt", new TrilhaAnimacao(3, 7, 128, 128, 3.0, 3.0, "./assets/Soldier_1/Hurt.png"));
    animacao.addTrilha("dead", new TrilhaAnimacao(3, 20, 128, 128, 3.0, 3.0, "./assets/Soldier_1/Dead.png", false));
    animacao.addTrilha("grenade", new TrilhaAnimacao(8, 10, 128, 128, 3.0, 3.0, "./assets/Soldier_1/Grenade.png", false));
    animacao.setPosition(px, py);
    animacao.setScale(SCALING_FACTOR, SCALING_FACTOR);
    setColisionBoxSize(sf::Vector2f(30 * SCALING_FACTOR, 128 * SCALING_FACTOR));
    visao.setPosition(px, py);
    setAnimationState();

    maxTiros += rand() % 3;
}

SoldadoChefe::~SoldadoChefe() {}

void SoldadoChefe::olhar()
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

    if (abs(distance) < 650)
    {
        if (tirosDisparados < maxTiros && tempoDisparo <= SHOT_ANIMATION_TIME && tempoUltimaGranada == 0.0f)
        {
            atacar();
            newState = SHOT;
        }
        else if (tirosDisparados >= maxTiros)
        {
            lancarGranada();
            newState = GRENADE;
        }
    }
    else
    {
        newState = IDLE;
    }
}

void SoldadoChefe::executar()
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
        else if (state == GRENADE)
        {
            if (tempoUltimaGranada > 0.0f)
            {
                tempoUltimaGranada += elapsed_time;
                if (tempoUltimaGranada >= GRENADE_COOLDOWN)
                {
                    tempoUltimaGranada = 0.0f;
                    tirosDisparados = 0;
                    numeroGranadas = 1;
                }
            }
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
            pFase->alteraPontos(500);
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

void SoldadoChefe::atacar()
{
    if (tempoDisparo >= COOLDOWN_TIRO)
    {
        Jogador *pJ = visao.getJogador();
        Projetil *proj = pFase->addProjetil(x + direcao * 120, y + (getSize().height / 9), direcao, SOLDADO);
        tempoDisparo = 0;
        tirosDisparados++;

        if (proj->getSize().intersects(pJ->getSize()))
        {
            danificar(pJ);
        }
    }
}

void SoldadoChefe::lancarGranada()
{

    float elapsed_time = pGG->getElapsedTime();
    tempoUltimaGranada += elapsed_time;
    if (numeroGranadas > 0 && tempoUltimaGranada > 1200.0f)
    {
        pFase->addGranada(x + direcao, y + (getSize().height / 9), direcao, SOLDADO);
        numeroGranadas--;
    }
}
void SoldadoChefe::danificar(Jogador *p)
{
    p->recebeDano(dano_projetil);
}

void SoldadoChefe::lidarColisao(sf::Vector2f intersecao, Entidade *other)
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

Json::Value SoldadoChefe::gravar()
{
    Json::Value entityJson;

    entityJson["type"] = getTipo();
    entityJson["x"] = getPosition().x;
    entityJson["y"] = getPosition().y;
    entityJson["vidas"] = getVidas();
    return entityJson;
}