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
    Personagem(float px, float py, int vidas);
    virtual ~Personagem();
    virtual void atacar() = 0;
    virtual void executar() override;
    virtual void desenhar();
    int getVidas();
    void recebeDano(int vidas_perdidas);
};

#endif // PERSONAGEM_HPP
