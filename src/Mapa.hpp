#ifndef MAPA_HPP
#define MAPA_HPP

#include <SFML/Graphics.hpp>
#include <vector>

class Mapa {
private:
    std::vector<sf::RectangleShape> blocos;

public:
    Mapa();
    void desenhar(sf::RenderWindow& window);
    void adicionarBloco(int x, int y);
    bool verificarColisao(const sf::FloatRect& boundingBox);
};

#endif // MAPA_HPP
