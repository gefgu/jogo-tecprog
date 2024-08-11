#ifndef ENTE_HPP
#define ENTE_HPP

#include "Gerenciadores/Gerenciador_Grafico.hpp"
// class Figura;

class Gerenciador_Grafico;

class Ente
{
protected:
  int id;
  static Gerenciador_Grafico *pGG;
  static int cont;
  // Figura *pFig;

public:
  Ente();
  ~Ente();
  virtual void executar() = 0;
  void desenhar();
  static void setGerenciadorGrafico(Gerenciador_Grafico *pGerenciador);
};

#endif // ENTE_HPP