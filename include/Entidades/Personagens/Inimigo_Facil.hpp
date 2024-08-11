#ifndef INIMIGO_FACIL_HPP
#define INIMIGO_FACIL_HPP

#include "Inimigo.hpp"
#include "Jogador.hpp"

class Inimigo_Facil : public Inimigo
{
private:
  float raio;

public:
  void executar();
  void danificar(Jogador *p);
};

#endif // INIMIGO_FACIL_HPP