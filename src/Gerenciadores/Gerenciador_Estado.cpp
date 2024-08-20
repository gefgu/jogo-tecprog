#include "Gerenciadores/Gerenciador_Estado.hpp"

Gerenciador_Estado::Gerenciador_Estado() : estado(MENUINICIO)
{
}

Gerenciador_Estado::~Gerenciador_Estado()
{
}

const estadoJogo Gerenciador_Estado::getEstadoJogo() const
{
  return estado;
}

const estadoJogo Gerenciador_Estado::getUltimoEstadoJogo() const
{
  return ultimoEstado;
}

void Gerenciador_Estado::setEstadoJogo(estadoJogo e)
{
  ultimoEstado = estado;
  estado = e;
}