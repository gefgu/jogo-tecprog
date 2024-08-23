#include "Entidades/Personagens/Personagem.hpp"
#include "Fases/Fase.hpp" // Full definition

const float GRAVIDADE = 9.8f;    // Aceleração da gravidade (em unidades por segundo^2)
const float TEMPO_FRAME = 0.16f; // Duração de cada frame (em segundos) - para 60 FPS
const float SCALING_FACTOR = 3.f;
const float DANO_COOLDOWN = 50.f;

Personagem::Personagem(int px, int py, float vx, float vy, int vidas, tipoDeEntidade tipo) : Entidade(px, py, tipo), num_vidas(vidas), velocidadeX(vx), velocidadeY(vy), colisionBox(), noChao(false), direcao(1), tempoDesdeUltimoPiso(COOLDOWN_PISO), state(IDLE), tempoDesdeUltimoDano(DANO_COOLDOWN * 100), mudouDirecao(false), newState(IDLE), tempoDesdeMorte(0.0f), morto(false),podeAnimar(true)
{
}

Personagem::~Personagem() {}

int Personagem::getVidas()
{
    return num_vidas;
}

void Personagem::recebeDano(int vidas_perdidas)
{
    if (tempoDesdeUltimoDano >= DANO_COOLDOWN)
    {
        num_vidas = max(0, num_vidas - vidas_perdidas);
        tempoDesdeUltimoDano = 0.0f;
        podeAnimar = false; 
        if (tipo == JOGADOR && tempoDesdeMorte == 0.0f)
        {
            pFase->alteraPontos(-100);
        }
    }
    if (tempoDesdeUltimoDano < 2)
    {
        podeAnimar = true;
    }
}

void Personagem::setColisionBoxSize(sf::Vector2f s)
{
    colisionBox = sf::RectangleShape(s);
    colisionBox.setOutlineColor(sf::Color::Red);
    sf::FloatRect size = colisionBox.getGlobalBounds();
    colisionBox.setOrigin(sf::Vector2f(size.width / 2.0f, size.height / 2.0f));
}

void Personagem::setColisionBoxPosition(int px, int py)
{
    colisionBox.setPosition(px, py);
}

void Personagem::aplicarGravidade()
{
        velocidadeY += GRAVIDADE * TEMPO_FRAME; // Aceleração devido à gravidade
        y += velocidadeY * TEMPO_FRAME;

    // if (!noChao)
    // {
    //     velocidadeY += GRAVIDADE * TEMPO_FRAME; // Aceleração devido à gravidade
    //     y += velocidadeY * TEMPO_FRAME;
    // }
}

void Personagem::setAnimationState()
{
    if (!podeAnimar)
    {
        return;
    }
    else if (state == IDLE)
    {
        animacao.setTrilha("idle");
    }
    else if (state == WALK)
    {
        animacao.setTrilha("walking");
    }
    else if (state == RUN)
    {
        animacao.setTrilha("running");
    }
    else if (state == JUMP)
    {
        animacao.setTrilha("jump");
    }
    else if (state == ATTACK)
    {
        animacao.setTrilha("attack");
    }
    else if (state == HURT)
    {
        animacao.setTrilha("hurt");
    }
    else if (state == DEAD)
    {
        animacao.setTrilha("dead");
    }
    else if (state == SHOT)
    {
        animacao.setTrilha("shot");
    }
    
    // Ajusta a escala com base na direção atual
    animacao.setScale(direcao * SCALING_FACTOR, SCALING_FACTOR);
}

void Personagem::setPosition(int px, int py)
{
    animacao.setPosition(px, py);
    colisionBox.setPosition(px, py);
    pGG->centerCamera(sf::Vector2f(px, py));
}

void Personagem::desenhar()
{
    animacao.desenhar();
    // pGG->draw(colisionBox);
}

sf::Vector2f Personagem ::getCenter()
{
    sf::FloatRect size = getSize();
    return sf::Vector2f(size.left + size.width / 2.0f, size.top + size.height / 2.0f);
}

int Personagem::getDirecao()
{
    return direcao;
}

sf::FloatRect Personagem ::getSize()
{
    return colisionBox.getGlobalBounds();
}

bool Personagem::getMorto()
{
    return morto;
}

