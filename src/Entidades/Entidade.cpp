#include "Entidades/Entidade.hpp"

Fase *Entidade::pFase(NULL);

Entidade::Entidade(int px, int py, tipoDeEntidade t) : Ente(), x(px), y(py), tipo(t), ativo(true)
{
}

Entidade::~Entidade() {}

const tipoDeEntidade Entidade::getTipo() const
{
    return tipo;
}

void Entidade::setFase(Fase *pF)
{
    pFase = pF;
}

const bool Entidade::getAtivo() const
{
    return ativo;
}

sf::Vector2f Entidade::getPosition()
{
    return sf::Vector2f(x, y);
}