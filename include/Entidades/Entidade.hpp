#ifndef ENTIDADE_HPP
#define ENTIDADE_HPP

#include <SFML/Graphics.hpp>

class Entidade {
protected:
    int x, y;
    sf::RectangleShape shape;

public:
    Entidade(int px, int py);
    virtual ~Entidade();
    virtual void executar() = 0;
    void desenhar(sf::RenderWindow& window);
};

#endif // ENTIDADE_HPP
