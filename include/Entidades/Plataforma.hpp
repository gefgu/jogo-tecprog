#pragma once

#include <SFML/Graphics.hpp>
#include "Entidades/Entidade.hpp"
#include "ElementosGraficos/ObjetoEstatico.hpp"

class Plataforma : public Entidade
{
private:
  ObjetoEstatico visual;

public:
  Plataforma(int px, int py); // posição e escala não mudam
  ~Plataforma();
  void desenhar();
}