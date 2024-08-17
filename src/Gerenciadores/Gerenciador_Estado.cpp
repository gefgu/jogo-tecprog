#include "Gerenciadores/Gerenciador_Estado.hpp"

Gerenciador_Estado::Gerenciador_Estado() : estado(MENU)
{
}

Gerenciador_Estado::~Gerenciador_Estado()
{
}

const estadoJogo Gerenciador_Estado::getEstadoJogo() const
{
  return estado;
}

void Gerenciador_Estado::setEstadoJogo(estadoJogo e)
{
  estado = e;
}