#ifndef PERSONAGEM_HPP
#define PERSONAGEM_HPP

#include "Entidades/Entidade.hpp"

class Personagem : public Entidade
{
protected:
    int num_vidas;

public:
    Personagem(float px, float py, int vidas);
    virtual ~Personagem();
    virtual void atacar() = 0;
    virtual void executar() override;
};

#endif // PERSONAGEM_HPP
