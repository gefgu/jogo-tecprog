#ifndef FASE_PRIMEIRA_HPP
#define FASE_PRIMEIRA_HPP

#include "Fase.hpp"
#include "Entidades/Personagens/Atirador.hpp"

class Veneza : public Fase
{
private:
  void criarCenario();
  void criaAtiradores();

public:
  Veneza(bool temP2, string filename = "", int pontos_iniciais = 1000);
  ~Veneza();
  void executar();
  void desenhar();
};

#endif // FASE_PRIMEIRA_HPP