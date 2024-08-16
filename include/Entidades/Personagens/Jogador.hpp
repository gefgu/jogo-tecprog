#ifndef JOGADOR_HPP
#define JOGADOR_HPP

#include "Entidades/Personagens/Personagem.hpp"
#include "ElementosGraficos/Animacao.hpp"
#include "ElementosGraficos/TrilhaAnimacao.hpp"

enum estadoJogador
{
    IDLE = 0,
    WALK,
    RUN,
    JUMP
};

class Jogador : public Personagem
{
private:
    float velocidadeY;
    float velocidadeX;
    float velocidadeCorrida;
    bool noChao;
    int direcao;
    Animacao animacao;
    estadoJogador state;

    void setAnimationState();
    void setPosition(int px, int py);

public:
    Jogador(float px, float py, int vidas);
    void atacar() override;
    void executar();
    void aplicarGravidade();
    void desenhar();
    sf::Vector2f getCenter();
    sf::FloatRect getSize();
    void lidarColisao(sf::Vector2f intersecao, Entidade *other);
};
#endif // JOGADOR_HPP
