#include "Entidade.hpp"

Entidade::Entidade(int px, int py) : x(px), y(py) {
    shape.setPosition(x, y);
    shape.setSize(sf::Vector2f(50.0f, 50.0f));
}

Entidade::~Entidade() {}

void Entidade::desenhar(sf::RenderWindow& window) {
    window.draw(shape);
}
