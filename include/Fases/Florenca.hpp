#ifndef FASE_SEGUNDA_HPP
#define FASE_SEGUNDA_HPP

#include "Fase.hpp"
#include "Entidades/Personagens/SoldadoChefe.hpp"

class Florenca : public Fase
{
private:
  void criarCenario();
  void criaMina();
  void criaSoldadoChefe();

public:
  Florenca(bool temP2, string filename = "", int pontos_iniciais = 1000);
  ~Florenca();
  void executar();
  void desenhar();
};

#endif // FASE_SEGUNDA_HPP