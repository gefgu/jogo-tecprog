#ifndef OBSTACULO_HPP
#define OBSTACULO_HPP

#include "Entidades/Entidade.hpp"

class Obstaculo : public Entidade
{
protected:
    bool danoso;

public:
    Obstaculo(int px, int py, bool dano);
    virtual ~Obstaculo();
    virtual void executar() override;
};

#endif // OBSTACULO_HPP
