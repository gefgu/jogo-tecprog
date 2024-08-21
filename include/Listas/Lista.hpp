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
  void remover(TL *elem);
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
void Lista<TL>::remover(TL *elem)
{
  if (!elem)
  {
    cout << "Ponteiro inválido em Lista.remover()" << endl;
    return;
  }

  Elemento<TL> *anterior = NULL;
  Elemento<TL> *atual = pPrimeiro;

  while (atual != NULL)
  {
    if (atual->getInfo() == elem)
    {
      if (anterior == NULL) // Element to remove is the first element
      {
        pPrimeiro = atual->getProximo();
      }
      else // Element to remove is in the middle or end
      {
        anterior->setProximo(atual->getProximo());
      }

      // Delete the element and free memory
      delete atual;
      return;
    }

    anterior = atual;
    atual = atual->getProximo();
  }

  // Element was not found
  cout << "Elemento não encontrado na lista." << endl;
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