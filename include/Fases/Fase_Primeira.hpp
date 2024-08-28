#ifndef FASE_PRIMEIRA_HPP
#define FASE_PRIMEIRA_HPP

#include "Fase.hpp"

class Fase_Primeira : public Fase
{
private:
  void criarCenario();

public:
  Fase_Primeira(bool temP2, string filename = NULL, int pontos_iniciais = 1000);
  ~Fase_Primeira();
  void executar();
  void criarInimigosFaceis();
  void criarObstaculosDificeis();
  void desenhar();
};

#endif // FASE_PRIMEIRA_HPP