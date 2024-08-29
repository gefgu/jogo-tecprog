#ifndef LISTA_HPP
#define LISTA_HPP

template <class TL>
class Lista
{
private:
  Elemento<TL> *pPrimeiro;
  Elemento<TL> *pUltimo;
  int _size;

  template <class TE>
  class Elemento
  {
  private:
    Elemento<TE> *pProx;
    TE *pInfo;

  public:
    Elemento(TE *elem);
    ~Elemento();
    TE *getInfo();
    Elemento<TE> *getProximo();
    void setProximo(Elemento<TE> *prox);
  };

  template <class TE>
  Elemento<TE>::Elemento(TE *elem) : pInfo(NULL), pProx(NULL)
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

  template <class TE>
  Elemento<TE>::~Elemento()
  {
    if (pInfo)
      delete pInfo;
  }

  template <class TE>
  TE *Elemento<TE>::getInfo()
  {
    return pInfo;
  }

  template <class TE>
  Elemento<TE> *Elemento<TE>::getProximo()
  {
    return pProx;
  }

  template <class TE>
  void Elemento<TE>::setProximo(Elemento<TE> *prox)
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

public:
  Lista();
  ~Lista();
  void incluir(TL *elem);
  void remover(TL *elem);
  Elemento<TL> *getPrimeiro();
  Elemento<TL> *getUltimo();
  int size();
  Elemento<TL> *operator[](int index); // Access by index
};

template <class TL>
Lista<TL>::Lista() : pPrimeiro(NULL), pUltimo(NULL), _size(0)
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
Elemento<TL> *Lista<TL>::getPrimeiro()
{
  return pPrimeiro;
}

template <class TL>
Elemento<TL> *Lista<TL>::getUltimo()
{
  return pUltimo;
}

template <class TL>
int Lista<TL>::size()
{
  return _size;
}

template <class TL>
Elemento<TL> *Lista<TL>::operator[](int index)
{
  if (index < 0 || index >= _size)
  {
    std::cout << "Index out of bounds in Lista.operator[]()." << std::endl;
    return NULL; // Or handle the error as needed
  }

  Elemento<TL> *current = pPrimeiro;
  for (int i = 0; i < index; i++)
  {
    current = current->getProximo();
  }
  return current;
}

#endif // LISTA_HPP