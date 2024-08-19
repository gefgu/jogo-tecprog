#ifndef FASE_SEGUNDA_HPP
#define FASE_SEGUNDA_HPP

#include "Fase.hpp"

class Fase_Segunda : public Fase
{
private:
  void criarCenario();

public:
  Fase_Segunda();
  ~Fase_Segunda();
  void executar();
  void criarInimigosFaceis();
  void criarObstaculosDificeis();
  void desenhar();
};

#endif // FASE_SEGUNDA_HPP