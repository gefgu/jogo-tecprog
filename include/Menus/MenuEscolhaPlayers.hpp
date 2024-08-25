#pragma once

#include "Menu.hpp"

using namespace std;

class MenuEscolhaPlayers : public Menu
{
private:
  bool twoPlayers;
  estadoJogo fase;

public:
  MenuEscolhaPlayers(estadoJogo proxFase);
  ~MenuEscolhaPlayers();
  void desenhar();
  void executar();
  void Update(const char *teclaPressionada);
  bool getTwoPlayers();
};