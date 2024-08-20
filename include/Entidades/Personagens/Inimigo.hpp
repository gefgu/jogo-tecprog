#ifndef INIMIGO_HPP
#define INIMIGO_HPP

#include "Personagem.hpp"

class Inimigo : public Personagem
{
protected:
    float ataque;

public:
    Inimigo(int px, int py, int vidas, float ataque);
    virtual ~Inimigo();
    void atacar() override;
    void executar() override;
};

#endif // INIMIGO_HPP
