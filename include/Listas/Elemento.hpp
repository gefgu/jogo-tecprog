#ifndef ELEMENTO_HPP
#define ELEMENTO_HPP

template <class TE>
class Elemento
{
private:
  Elemento<TE> *pProx;
  TE pInfo;
}

#endif // ELEMENTO_HPP