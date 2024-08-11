#ifndef GERENCIADOR_COLISOES_HPP
#define GERENCIADOR_COLISOES_HPP

#include "vector"
#include "list"
#include "Inimigo.hpp"
#include "Obstaculo.hpp"

using namespace std;

class Gerenciador_Colisoes
{
private:
  vector<Inimigo *> LIs;
  list<Obstaculo *> LOs;

public:
  Gerenciador_Colisoes();
  ~Gerenciador_Colisoes();
  void incluirObstaculo();
  void tratarColisoesJogsObstaculos();
  void tratarColisoesJogsInimigos();
}

#endif // GERENCIADOR_COLISOES_HPP