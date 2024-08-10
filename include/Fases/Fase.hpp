#include "Ente.hpp"

class Fase : public Ente
{
public:
  virtual void executar() = 0;
  void gerenciar_colisoes();
  void criarInimMedios();
  void criarObstaculosMedios();
}