#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string> // Para usar std::string
#include "Gerenciadores/Gerenciador_Grafico.hpp"
#include "Gerenciadores/Gerenciador_Estado.hpp"
#include "Menus/Menu.hpp"
#include "Menus/CampoDeTexto.hpp"

using namespace std;

class Pause : public Menu
{
private:
  estadoJogo ultimaFase;

public:
  Pause(estadoJogo ultimoEstado);
  ~Pause();

  void desenhar();
  void executar();
};
