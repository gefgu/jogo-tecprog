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
  CampoDeTexto textInput;
  estadoJogo ultimaFase;

public:
  MenuFimDeJogo(int p, estadoJogo ultimoEstado); // pontos
  ~MenuFimDeJogo();

  void desenhar();
  void executar();
  void encerrar();
  void salvar();
  int getPontos();
  void Update(const char *teclaPressionada);
};
