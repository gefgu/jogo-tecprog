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

public:
    Jogador(float px, float py, int vidas);
    void atacar() override;
    void executar();
    void aplicarGravidade();
    void desenhar();
};
#endif // JOGADOR_HPP
