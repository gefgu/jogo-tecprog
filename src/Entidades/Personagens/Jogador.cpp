#include "Entidades/Personagens/Jogador.hpp"
#include <cmath> // Para usar std::max

const float GRAVIDADE = 9.8f;     // Aceleração da gravidade (em unidades por segundo^2)
const float TEMPO_FRAME = 0.016f; // Duração de cada frame (em segundos) - para 60 FPS

const string IDLE_P1_PATH = "./assets/Gangsters_1/Idle.png";

Jogador::Jogador(float px, float py, int vidas) : Personagem(px, py, vidas),
                                                  velocidadeY(0), noChao(false)
{
    shape.setFillColor(sf::Color::Green); // Cor diferente para o jogador
    sf::Texture textura = pGG->carregaTextura(IDLE_P1_PATH);
    sprite.setTexture(textura);
    sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
}

void Jogador::atacar()
{
    // Implementação do ataque do jogador
}

void Jogador::executar()
{
    aplicarGravidade();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        x -= 100 * TEMPO_FRAME; // Movimentação horizontal ajustada para 200 unidades/segundo
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        x += 100 * TEMPO_FRAME;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && noChao)
    {
        velocidadeY = -sqrt(2 * GRAVIDADE * 80); // Cálculo da velocidade inicial para alcançar 150 unidades de altura
        noChao = false;
    }

    shape.setPosition(x, y);
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

    shape.setPosition(x, y);
}
