#include "Ente.hpp"

int Ente::cont(0);
Gerenciador_Grafico *Ente::pGG(NULL);

void Ente::setGerenciadorGrafico(Gerenciador_Grafico *pGerenciador)
{
  pGG = pGerenciador;
}

Ente::Ente() : id(cont++)
{
}

Ente::~Ente() {}
