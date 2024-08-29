#ifndef FASE_SEGUNDA_HPP
#define FASE_SEGUNDA_HPP

#include "Fase.hpp"
#include "Entidades/Personagens/SoldadoChefe.hpp"

class Fase_Segunda : public Fase
{
private:
  void criarCenario();
  void criaMina();
  void criaSoldadoChefe();

public:
  Fase_Segunda(bool temP2, int pontos_iniciais = 1000);
  ~Fase_Segunda();
  void executar();
  void desenhar();
};

#endif // FASE_SEGUNDA_HPP