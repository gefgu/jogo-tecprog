#include "ListaEntidades.hpp"

ListaEntidades::ListaEntidades() {}

ListaEntidades::~ListaEntidades() {}

void ListaEntidades::incluir(Entidade *pE)
{
  LEs.incluir(pE);
}

void percorrer()
{
  Elemento<Entidade> it;
  for (it = LEs.getPrimeiro(); it != NULL; it = it->getProximo())
  {
    it->getInfo()->executar();
  }
}