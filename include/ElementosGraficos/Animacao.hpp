#pragma once

#include <SFML/Graphics.hpp>
#include "Gerenciadores/Gerenciador_Grafico.hpp"
#include "ElementosGraficos/TrilhaAnimacao.hpp"
#include <map>
#include <iostream>

using namespace std;

class Animacao
{
private:
  map<const char *, TrilhaAnimacao *> trilhas;
  TrilhaAnimacao *trilhaAtual;

public:
  Animacao();
  ~Animacao();
  void addTrilha(const char *key, TrilhaAnimacao *trilha);
  void setTrilha(const char *key);
  void update();
  void setPosition(int px, int py);
  void setScale(float sx, float sy);
  void desenhar();
};