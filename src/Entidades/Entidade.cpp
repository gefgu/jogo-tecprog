#include "Entidades/Entidade.hpp"

Entidade::Entidade(tipoDeEntidade t) : Ente(), tipo(t)
{
    // shape.setPosition(x, y);
    // shape.setSize(sf::Vector2f(50.0f, 50.0f));
}

Entidade::~Entidade() {}

void Entidade::desenhar(sf::RenderWindow &window)
{
    window.draw(shape);
}

void Entidade::desenhar()
{
    if (pGG)
    {
        // pGG->desenharEnte(this);
    }
    else
    {
        cout << "Gerenciador Gráfico não encontrado em Entidade" << endl;
    }
}

sf::Vector2f Entidade::getCenter() {}
sf::FloatRect Entidade::getSize() {}

const tipoDeEntidade Entidade::getTipo() const
{
    return tipo;
}