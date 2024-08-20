#include "Entidades/Personagens/Personagem.hpp"

Personagem::Personagem(int px, int py, float vx, float vy, int vidas) : Entidade(px, py, tipoDeEntidade::JOGADOR), num_vidas(vidas), velocidadeX(vx), velocidadeY(vy), colisionBox()
{
}

Personagem::~Personagem() {}

void Personagem::executar()
{
    // Implementação genérica, pode ser sobrescrita pelas subclasses
}

void Personagem::desenhar() {}

int Personagem::getVidas()
{
    return num_vidas;
}

void Personagem::recebeDano(int vidas_perdidas)
{
    num_vidas = max(0, num_vidas - vidas_perdidas);
}

void Personagem::setColisionBoxSize(sf::Vector2f s)
{
    colisionBox = sf::RectangleShape(s);
    colisionBox.setOutlineColor(sf::Color::Red);
    sf::FloatRect size = colisionBox.getGlobalBounds();
    colisionBox.setOrigin(sf::Vector2f(size.width / 2.0f, size.height / 2.0f));
}
void Personagem::setColisionBoxPosition(int px, int py)
{
    colisionBox.setPosition(px, py);
}