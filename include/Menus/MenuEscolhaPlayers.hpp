#pragma once

#include "Menu.hpp"
#include "Gerenciadores/Configuracoes.hpp"

using namespace std;

class MenuEscolhaPlayers : public Menu
{
private:
  Configuracoes &configuracoes;
  estadoJogo fase;

public:
  MenuEscolhaPlayers(estadoJogo proxFase);
  ~MenuEscolhaPlayers();
  void desenhar();
  void executar();
  void Update(const char *teclaPressionada);
};