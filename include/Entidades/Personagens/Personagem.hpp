#ifndef PERSONAGEM_HPP
#define PERSONAGEM_HPP

#include "Entidades/Entidade.hpp"

class Personagem : public Entidade
{
protected:
    int num_vidas;
    float velocidadeX; // em unidades por segundo
    float velocidadeY; // em unidades por segundo

public:
    Personagem(int px, int py, float vx, float vy, int vidas);
    virtual ~Personagem();
    virtual void atacar() = 0;
    virtual void executar() = 0;
    virtual void desenhar() = 0;
    virtual void setPosition(int px, int py) = 0;
    int getVidas();
    void recebeDano(int vidas_perdidas);
};

#endif // PERSONAGEM_HPP
