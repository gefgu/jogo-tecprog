#include "Gerenciadores/Configuracoes.hpp"

Configuracoes::Configuracoes() : doisJogadores(false) {}

Configuracoes::~Configuracoes() {}

void Configuracoes::setDoisJogadores(bool dois)
{
  doisJogadores = dois;
}

bool Configuracoes::getDoisJogadores()
{
  return doisJogadores;
}