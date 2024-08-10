#ifndef ELEMENTO_HPP
#define ELEMENTO_HPP

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
}

#endif // ELEMENTO_HPP