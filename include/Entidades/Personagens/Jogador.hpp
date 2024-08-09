#ifndef JOGADOR_HPP
#define JOGADOR_HPP

#include "Personagem.hpp"

class Jogador : public Personagem {
private:
    float velocidadeY;
    bool noChao;

public:
    Jogador(float px, float py, int vidas);
    void atacar() override;
    void executar();
    void aplicarGravidade();
};
#endif // JOGADOR_HPP
