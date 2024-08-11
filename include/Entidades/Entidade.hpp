#ifndef ENTIDADE_HPP
#define ENTIDADE_HPP

#include <SFML/Graphics.hpp>
#include "Ente.hpp"

class Entidade : public Ente
{
protected:
    int x, y;
    sf::RectangleShape shape;

public:
    Entidade(int px, int py);
    virtual ~Entidade();
    virtual void executar() = 0;
    void desenhar(sf::RenderWindow &window);
    // virtual void desenhar();
};

#endif // ENTIDADE_HPP
