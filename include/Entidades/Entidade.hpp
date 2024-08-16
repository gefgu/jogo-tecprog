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
    Entidade();
    virtual ~Entidade();
    virtual void executar() = 0;
    void desenhar(sf::RenderWindow &window);
    virtual void desenhar();
    virtual sf::Vector2f getCenter();
    virtual sf::FloatRect getSize();
    virtual void lidarColisao(sf::Vector2f intersecao, Entidade *other) = 0;
};

#endif // ENTIDADE_HPP
