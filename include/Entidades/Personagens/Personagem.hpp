#ifndef PERSONAGEM_HPP
#define PERSONAGEM_HPP

#include "Entidades/Entidade.hpp"
#include "ElementosGraficos/Animacao.hpp"

const float COOLDOWN_PISO = 75.f;

enum estadoPersonagem
{
    IDLE = 0,
    WALK,
    RUN,
    JUMP
};

class Personagem : public Entidade
{
protected:
    estadoPersonagem state;
    int num_vidas;
    float velocidadeX; // em unidades por segundo
    float velocidadeY; // em unidades por segundo
    bool noChao;
    int direcao;
    float tempoDesdeUltimoPiso;
    sf::RectangleShape colisionBox;
    Animacao animacao;
    void setAnimationState();
    void setPosition(int px, int py);
    void aplicarGravidade();

public:
    Personagem(int px, int py, float vx, float vy, int vidas, tipoDeEntidade tipo);
    virtual ~Personagem();
    virtual void atacar() = 0;
    virtual void executar() = 0;
    virtual void lidarColisao(sf::Vector2f intersecao, Entidade *other) = 0;
    int getVidas();
    void desenhar();
    void recebeDano(int vidas_perdidas);
    void setColisionBoxSize(sf::Vector2f s);
    void setColisionBoxPosition(int px, int py);
    sf::Vector2f getCenter();
    sf::FloatRect getSize();
};

#endif // PERSONAGEM_HPP
