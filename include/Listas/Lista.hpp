#ifndef LISTA_HPP
#define LISTA_HPP

#include "Elemento.hpp"

template <class TL>
class Lista
{
private:
  Elemento<TL> *pPrimeiro;
  Elemento<TL> *pUltimo;

public:
  Lista();
  ~Lista();
  void incluir(TL *elem);
  Elemento<TL> *getPrimeiro();
  Elemento<TL> *getUltimo();
};

template <class TL>
Lista<TL>::Lista() : pPrimeiro(NULL), pUltimo(NULL)
{
}

template <class TL>
Lista<TL>::~Lista()
{
  Elemento<TL> *ultimo = pPrimeiro;
  Elemento<TL> *atual;
  do
  {
    atual = ultimo->getProximo();
    delete ultimo;
    ultimo = atual;
  } while (ultimo != pUltimo);
  pPrimeiro = NULL;
  pUltimo = NULL;
}

template <class TL>
void Lista<TL>::incluir(TL *elem)
{
  if (elem)
  {
    if (pPrimeiro == NULL)
    {
      Elemento<TL> *e = new Elemento(elem);
      pPrimeiro = e;
      pUltimo = e;
    }
    else
    {
      Elemento<TL> *e = new Elemento(elem);
      pUltimo->setProximo(e);
      pUltimo = e;
    }
  }
  else
  {
    cout << "Ponteiro inválido em Lista.incluir()" << endl;
  }
}

template <class TL>
Elemento<TL> *Lista<TL>::getPrimeiro()
{
  return pPrimeiro;
}

template <class TL>
Elemento<TL> *Lista<TL>::getUltimo()
{
  return pUltimo;
}

#endif // LISTA_HPP