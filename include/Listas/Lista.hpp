#ifndef LISTA_HPP
#define LISTA_HPP

#include <iostream> // Add this for cout
using namespace std;

template <class TL>
class Lista
{
public:
  class Elemento; // Forward declare Elemento class

private:
  Elemento *pPrimeiro;
  Elemento *pUltimo;
  int _size;

public:
  Lista();
  ~Lista();
  void incluir(TL *elem);
  void remover(TL *elem);
  Elemento *getPrimeiro();
  Elemento *getUltimo();
  int size();
  Elemento *operator[](int index); // Access by index

  // Nested Elemento class definition
  class Elemento
  {
  private:
    Elemento *pProx;
    TL *pInfo;

  public:
    Elemento(TL *elem);
    ~Elemento();
    TL *getInfo();
    Elemento *getProximo();
    void setProximo(Elemento *prox);
  };
};

// Definitions for Lista class
template <class TL>
Lista<TL>::Lista() : pPrimeiro(NULL), pUltimo(NULL), _size(0)
{
}

template <class TL>
Lista<TL>::~Lista()
{
  Elemento *ultimo = pPrimeiro;
  Elemento *atual;
  while (ultimo != NULL)
  {
    atual = ultimo->getProximo();
    delete ultimo;
    ultimo = atual;
  }
  pPrimeiro = NULL;
  pUltimo = NULL;
}

template <class TL>
void Lista<TL>::incluir(TL *elem)
{
  if (elem)
  {
    Elemento *e = new Elemento(elem);
    if (pPrimeiro == NULL)
    {
      pPrimeiro = e;
      pUltimo = e;
    }
    else
    {
      pUltimo->setProximo(e);
      pUltimo = e;
    }
    _size++;
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

  Elemento *anterior = NULL;
  Elemento *atual = pPrimeiro;

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

      _size--;
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
typename Lista<TL>::Elemento *Lista<TL>::getPrimeiro()
{
  return pPrimeiro;
}

template <class TL>
typename Lista<TL>::Elemento *Lista<TL>::getUltimo()
{
  return pUltimo;
}

template <class TL>
int Lista<TL>::size()
{
  return _size;
}

template <class TL>
typename Lista<TL>::Elemento *Lista<TL>::operator[](int index)
{
  if (index < 0 || index >= _size)
  {
    std::cout << "Index out of bounds in Lista.operator[]()." << std::endl;
    return NULL; // Or handle the error as needed
  }

  Elemento *current = pPrimeiro;
  for (int i = 0; i < index; i++)
  {
    current = current->getProximo();
  }
  return current;
}

// Definitions for nested Elemento class
template <class TL>
Lista<TL>::Elemento::Elemento(TL *elem) : pInfo(NULL), pProx(NULL)
{
  if (elem)
  {
    pInfo = elem;
  }
  else
  {
    cout << "Ponteiro inválido na criação do Elemento" << endl;
  }
}

template <class TL>
Lista<TL>::Elemento::~Elemento()
{
  if (pInfo)
    delete pInfo;
}

template <class TL>
TL *Lista<TL>::Elemento::getInfo()
{
  return pInfo;
}

template <class TL>
typename Lista<TL>::Elemento *Lista<TL>::Elemento::getProximo()
{
  return pProx;
}

template <class TL>
void Lista<TL>::Elemento::setProximo(Elemento *prox)
{
  if (prox)
  {
    pProx = prox;
  }
  else
  {
    cout << "Ponteiro inválido em Elemento.setProximo()" << endl;
  }
}

#endif // LISTA_HPP
