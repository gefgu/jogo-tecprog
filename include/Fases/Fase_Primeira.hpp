#ifndef FASE_PRIMEIRA_HPP
#define FASE_PRIMEIRA_HPP

#include "Fase.hpp"
#include "Entidades/Personagens/Atirador.hpp"

class Fase_Primeira : public Fase
{
private:
  void criarCenario();
  void criaAtiradores();
public:
  Fase_Primeira(bool temP2, string filename = "", int pontos_iniciais = 1000);
  ~Fase_Primeira();
  void executar();
  void desenhar();
};

#endif // FASE_PRIMEIRA_HPP