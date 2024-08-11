#include "Listas/ListaEntidades.hpp"

ListaEntidades::ListaEntidades() {}

ListaEntidades::~ListaEntidades() {}

void ListaEntidades::incluir(Entidade *pE)
{
  LEs.incluir(pE);
}

void ListaEntidades::executar()
{
  Elemento<Entidade> *it;
  for (it = LEs.getPrimeiro(); it != NULL; it = it->getProximo())
  {
    it->getInfo()->executar();
  }
}

void ListaEntidades::desenhar()
{
  Elemento<Entidade> *it;
  for (it = LEs.getPrimeiro(); it != NULL; it = it->getProximo())
  {
    it->getInfo()->desenhar();
  }
}