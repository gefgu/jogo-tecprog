#pragma once

#include "Menu.hpp"

using namespace std;

class MenuInicio : public Menu
{
protected:
public:
  MenuInicio();
  ~MenuInicio();
  void desenhar();
  void executar();
  void Update(const char *teclaPressionada);
};