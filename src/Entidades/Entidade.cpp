#include "Entidades/Entidade.hpp"

Fase *Entidade::pFase(NULL);

Entidade::Entidade(int px, int py, tipoDeEntidade t) : Ente(), x(px), y(py), tipo(t)
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