#include "Mapa.hpp"

Mapa::Mapa() {
    // Adiciona blocos para o "chão" e alguns obstáculos
    adicionarBloco(0, 550);
    adicionarBloco(50, 550);
    adicionarBloco(100, 550);
    adicionarBloco(150, 550);
    adicionarBloco(200, 550);
    adicionarBloco(250, 550);
    adicionarBloco(300, 550);
    adicionarBloco(350, 550);
    adicionarBloco(400, 550);
    adicionarBloco(450, 550);
    adicionarBloco(500, 550);
    adicionarBloco(550, 550);
    adicionarBloco(600, 550);
    adicionarBloco(650, 550);
    adicionarBloco(700, 550);
    adicionarBloco(750, 550);

    adicionarBloco(300, 450);
    adicionarBloco(350, 450);
    adicionarBloco(400, 450);
}

void Mapa::desenhar(sf::RenderWindow& window) {
    for (auto& bloco : blocos) {
        window.draw(bloco);
    }
}

void Mapa::adicionarBloco(int x, int y) {
    sf::RectangleShape bloco(sf::Vector2f(50.0f, 50.0f));
    bloco.setPosition(x, y);
    bloco.setFillColor(sf::Color::Blue);
    blocos.push_back(bloco);
}

bool Mapa::verificarColisao(const sf::FloatRect& boundingBox) {
    for (auto& bloco : blocos) {
        if (bloco.getGlobalBounds().intersects(boundingBox)) {
            return true;
        }
    }
    return false;
}
