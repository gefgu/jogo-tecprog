#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string> // Para usar std::string
#include "Gerenciadores/Gerenciador_Grafico.hpp"
#include "Gerenciadores/Gerenciador_Estado.hpp"

using namespace std;

class MenuFimDeJogo
{
private:
  sf::Sprite fundo; // Fundo do menu
  int pontos;
  Gerenciador_Grafico &gerenciadorGrafico;
  Gerenciador_Estado &gerenciadorEstado;
  sf::Text textoFinal;

public:
  MenuFimDeJogo(int p); // pontos
  ~MenuFimDeJogo();

  void desenhar();
  void executar();
};
