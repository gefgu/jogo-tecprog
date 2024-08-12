#include "Entidades/Personagens/Jogador.hpp"
#include <cmath> // Para usar std::max

const float GRAVIDADE = 9.8f;     // Aceleração da gravidade (em unidades por segundo^2)
const float TEMPO_FRAME = 0.016f; // Duração de cada frame (em segundos) - para 60 FPS

const string IDLE_P1_PATH = "./assets/Gangsters_1/Idle.png";

const int ANIMATION_FRAMES_BEFORE_CHANGE = 24;

Jogador::Jogador(float px, float py, int vidas) : Personagem(px, py, vidas),
                                                  velocidadeY(0), noChao(false), animation_index(0), animation_max_frames(5 * ANIMATION_FRAMES_BEFORE_CHANGE)
{

    carregaTextura(IDLE_P1_PATH);
    sprite.setTexture(textura);
    sprite.setTextureRect(sf::IntRect(0, 0, 128, 128));
    sprite.scale(3, 3);
    // sprite.setColor(sf::Color::Red); // Cor diferente para o jogador

}

void Jogador::atacar()
{
    // Implementação do ataque do jogador
}

void Jogador::executar()
{
    // aplicarGravidade();

    float elapsed_time = pGG->getElapsedTime();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        x -= velocidadeX * (elapsed_time / 100.0);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        x += velocidadeX * (elapsed_time / 100.0);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && noChao)
    {
        velocidadeY = -sqrt(2 * GRAVIDADE * 80); // Cálculo da velocidade inicial para alcançar 150 unidades de altura
        noChao = false;
    }

    sprite.setPosition(x, y);
    if (animation_index < animation_max_frames)
    {
        animation_index++;
    }
    else
    {
        animation_index = 0;
    }
    sprite.setTextureRect(sf::IntRect(128 * (animation_index / (int)ANIMATION_FRAMES_BEFORE_CHANGE), 0, 128, 128));
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
