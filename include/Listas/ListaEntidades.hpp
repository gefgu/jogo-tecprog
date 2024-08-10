#ifndef LISTAENTIDADES_HPP
#define LISTAENTIDADES_HPP

#include "Entidade.hpp"
#include "Lista.hpp"

class ListaEntidades
{
private:
  Lista<Entidade> LEs;

public:
  ListaEntidades();
  ~ListaEntidades();
  void incluir(Entidade *pE);
  void percorrer();
}

#endif // LISTAENTIDADES_HPP