#ifndef ELEMENTO_HPP
#define ELEMENTO_HPP
#include <iostream>

using namespace std;

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

#endif // ELEMENTO_HPP