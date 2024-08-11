#ifndef JOGADOR_HPP
#define JOGADOR_HPP

#include "Entidades/Personagens/Personagem.hpp"

class Jogador : public Personagem
{
private:
    float velocidadeY;
    bool noChao;
    int animation_index;
    int animation_max_frames;

public:
    Jogador(float px, float py, int vidas);
    void atacar() override;
    void executar();
    void aplicarGravidade();
};
#endif // JOGADOR_HPP
