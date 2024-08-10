#ifndef LISTA_HPP
#define LISTA_HPP

#include "Elemento.hpp"

template <class TL>
class Lista
{
private:
  Elemento<TL> *pPrimeiro;
  Element<TL> *pUltimo;
}

#endif // LISTA_HPP