#ifndef LISTAENTIDADES_HPP
#define LISTAENTIDADES_HPP

#include "Entidades/Entidade.hpp"
#include "Listas/Lista.hpp"
#include <json/json.h> // JSON library that supports C++03

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
  Json::Value toJsonArray();
};

#endif // LISTAENTIDADES_HPP