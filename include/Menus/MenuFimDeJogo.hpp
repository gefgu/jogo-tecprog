#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string> // Para usar std::string
#include "Gerenciadores/Gerenciador_Grafico.hpp"
#include "Gerenciadores/Gerenciador_Estado.hpp"
#include "Menus/Menu.hpp"
#include "Menus/CampoDeTexto.hpp"

using namespace std;

class MenuFimDeJogo : public Menu
{
private:
  int pontos;
  Gerenciador_Estado &gerenciadorEstado;
  CampoDeTexto textInput;

public:
  MenuFimDeJogo(int p); // pontos
  ~MenuFimDeJogo();

  void desenhar();
  void executar();
  void encerrar();
  void salvar();
  int getPontos();
};
