#include "Ente.hpp"

class BiblioGrafica;

class Gerenciador_Grafico
{
private:
  BiblioGrafica obj;

public:
  Gerenciador_Grafico();
  ~Gerenciador_Grafico();
  void desenharEnte(Ente *pE);
}