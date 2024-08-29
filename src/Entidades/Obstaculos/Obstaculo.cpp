#include "Entidades/Obstaculos/Obstaculo.hpp"

Obstaculo::Obstaculo(int px, int py, const char *img_path, tipoDeEntidade tipo) : Entidade(px, py, tipo), visual(img_path, true) {}

Obstaculo::~Obstaculo() {}

sf::Vector2f Obstaculo::getCenter()
{
    return visual.getCenter();
}

sf::FloatRect Obstaculo::getSize()
{
    return visual.getSize();
}

void Obstaculo::desenhar()
{
    visual.desenhar();
}
