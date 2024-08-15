#include "Entidades/Personagens/Jogador.hpp"
#include <cmath> // Para usar std::max

const float GRAVIDADE = 9.8f;    // Aceleração da gravidade (em unidades por segundo^2)
const float TEMPO_FRAME = 0.16f; // Duração de cada frame (em segundos) - para 60 FPS

Jogador::Jogador(float px, float py, int vidas) : Personagem(px, py, vidas),
                                                  velocidadeY(0), noChao(false),
                                                  animacao()
{
    animacao.addTrilha("idle", new TrilhaAnimacao(5, 15, 128, 128, 3, 3, "./assets/Gangsters_1/Idle.png"));
    animacao.addTrilha("running", new TrilhaAnimacao(9, 10, 128, 128, 3, 3, "./assets/Gangsters_1/Run.png"));
    animacao.addTrilha("jump", new TrilhaAnimacao(9, 10, 128, 128, 3, 3, "./assets/Gangsters_1/Jump.png"));
    state = IDLE;
    animacao.setPosition(x, y);
    setAnimationState();
}

void Jogador::setAnimationState()
{
    if (state == IDLE)
    {
        animacao.setTrilha("idle");
    }
    else if (state == RUN)
    {
        animacao.setTrilha("running");
    }
    else if (state == JUMP)
    {
        animacao.setTrilha("jump");
    }
}

void Jogador::atacar()
{
    // Implementação do ataque do jogador
}

void Jogador::executar()
{
    aplicarGravidade();
    estadoJogador newState = IDLE;

    float elapsed_time = pGG->getElapsedTime();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        x -= velocidadeX * (elapsed_time / 100.0);
        newState = RUN;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        x += velocidadeX * (elapsed_time / 100.0);
        newState = RUN;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && noChao)
    {
        velocidadeY = -sqrt(2 * GRAVIDADE * 100); // Cálculo da velocidade inicial para alcançar 150 unidades de altura
        noChao = false;
    }
    if (!noChao)
    {
        newState = JUMP;
    }

    if (newState != state)
    {
        state = newState;
        setAnimationState();
    }

    animacao.update();
    animacao.setPosition(x, y);
}

void Jogador::aplicarGravidade()
{
    if (!noChao)
    {
        velocidadeY += GRAVIDADE * TEMPO_FRAME; // Aceleração devido à gravidade
        y += velocidadeY * TEMPO_FRAME;
    }

    if (y >= 500)
    { // "Chão" do jogo
        y = 500;
        velocidadeY = 0;
        noChao = true;
    }
}

void Jogador::desenhar()
{
    animacao.desenhar();
}
