#ifndef JOGADOR_HPP
#define JOGADOR_HPP

#include "Entidades/Personagens/Personagem.hpp"
#include "ElementosGraficos/TrilhaAnimacao.hpp"

class Jogador : public Personagem
{
private:
    float velocidadeY;
    bool noChao;
    TrilhaAnimacao trilha;

public:
    Jogador(float px, float py, int vidas);
    void atacar() override;
    void executar();
    void aplicarGravidade();
    void desenhar();
};
#endif // JOGADOR_HPP
