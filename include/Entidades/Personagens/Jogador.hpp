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
    float velocidadeCorrida;
    bool noChao;
    int direcao;
    Animacao animacao;
    estadoJogador state;
    float tempoDesdeUltimoPulo;
    float tempoDesdeUltimoEspinho;
    Entidade *ultimoPiso;

    void setAnimationState();
    void setPosition(int px, int py);
    bool estaNoChao();
    void mover();

public:
    Jogador(int px, int py, int vidas);
    void atacar() override;
    void executar();
    void aplicarGravidade();
    void desenhar();
    sf::Vector2f getCenter();
    sf::FloatRect getSize();
    void lidarColisao(sf::Vector2f intersecao, Entidade *other);
};
#endif // JOGADOR_HPP
