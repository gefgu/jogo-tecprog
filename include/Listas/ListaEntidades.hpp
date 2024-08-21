#ifndef LISTAENTIDADES_HPP
#define LISTAENTIDADES_HPP

#include "Entidades/Entidade.hpp"
#include "Listas/Lista.hpp"

class ListaEntidades
{
private:
  Lista<Entidade> LEs;

public:
  ListaEntidades();
  ~ListaEntidades();
  void incluir(Entidade *pE);
  void remover(Entidade *pE);
  void executar();
  void desenhar();
  Entidade *getRandom();
};

#endif // LISTAENTIDADES_HPP