#include "Inimigo.hpp"
#include "Jogador.hpp"

class Inimigo_Facil : public Inimigo
{
private:
  float raio;

public:
  void executar();
  void danificar(Jogador *p);
}