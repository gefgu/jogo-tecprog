#ifndef OBSTACULO_HPP
#define OBSTACULO_HPP

#include "Entidades/Entidade.hpp"

class Obstaculo : public Entidade
{
public:
    Obstaculo(int px, int py, tipoDeEntidade tipo = tipoDeEntidade::OBSTACULO);
    virtual ~Obstaculo();
    virtual void executar() = 0;
    virtual sf::Vector2f getCenter() = 0;
    virtual sf::FloatRect getSize() = 0;
    virtual void desenhar() = 0;
};

#endif // OBSTACULO_HPP
