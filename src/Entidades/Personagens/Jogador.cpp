#include "Entidades/Personagens/Jogador.hpp"
#include <cmath> // Para usar std::max

const float GRAVIDADE = 9.8f;    // Aceleração da gravidade (em unidades por segundo^2)
const float TEMPO_FRAME = 0.16f; // Duração de cada frame (em segundos) - para 60 FPS

Jogador::Jogador(float px, float py, int vidas) : Personagem(px, py, vidas),
                                                  velocidadeY(0), noChao(false),
                                                  trilha(5, 15, 128, 128, 3, 3, "./assets/Gangsters_1/Idle.png")
{
    x = px;
    y = py;
    trilha.setPosition(x, y);
}

void Jogador::atacar()
{
    // Implementação do ataque do jogador
}

void Jogador::executar()
{
    aplicarGravidade();

    float elapsed_time = pGG->getElapsedTime();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        x -= velocidadeX * (elapsed_time / 100.0);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        x += velocidadeX * (elapsed_time / 100.0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && noChao)
    {
        velocidadeY = -sqrt(2 * GRAVIDADE * 100); // Cálculo da velocidade inicial para alcançar 150 unidades de altura
        noChao = false;
    }

    trilha.update();
    trilha.setPosition(x, y);
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

    trilha.setPosition(x, y);
}

void Jogador::desenhar()
{
    trilha.desenhar();
}
