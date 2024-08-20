#ifndef OBSTACULO_HPP
#define OBSTACULO_HPP

#include "Entidades/Entidade.hpp"
#include "ElementosGraficos/ObjetoEstatico.hpp"

class Obstaculo : public Entidade
{
protected:
    ObjetoEstatico visual;

public:
    Obstaculo(int px, int py, const char *img_path, tipoDeEntidade tipo = tipoDeEntidade::OBSTACULO);
    ~Obstaculo();
    virtual void executar() = 0;
    sf::Vector2f getCenter();
    sf::FloatRect getSize();
    void desenhar();
};

#endif // OBSTACULO_HPP
