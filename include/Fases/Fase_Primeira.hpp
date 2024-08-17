#ifndef FASE_PRIMEIRA_HPP
#define FASE_PRIMEIRA_HPP

#include "Fase.hpp"

class Fase_Primeira : public Fase
{

public:
  Fase_Primeira();
  ~Fase_Primeira();
  void executar();
  void criarInimigosFaceis();
  void criarObstaculosDificeis();
  void desenhar();
};

#endif // FASE_PRIMEIRA_HPP