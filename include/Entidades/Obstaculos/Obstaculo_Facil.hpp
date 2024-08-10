#include "Obstaculo.hpp"
#include "Jogador.hpp"

class Obstaculo_Facil : public Obstaculo
{
private:
  int elasticidade;

public:
  void executar();
  void obstacular(Jogador *p);
}