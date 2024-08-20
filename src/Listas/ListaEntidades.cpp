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

Entidade *ListaEntidades::getRandom()
{
  Elemento<Entidade> *it;
  for (it = LEs.getPrimeiro(); it != NULL; it = it->getProximo())
  {
    if ((rand() % 100) == 0)
      return it->getInfo();

    if (it->getProximo() == NULL)
      it = LEs.getPrimeiro();
  }
  return LEs.getPrimeiro()->getInfo();
}