#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string> // Para usar std::string
#include "Gerenciadores/Gerenciador_Grafico.hpp"
#include "Gerenciadores/Gerenciador_Estado.hpp"
#include "Menus/Menu.hpp"
#include "Menus/CampoDeTexto.hpp"

using namespace std;

class MenuCarregamento : public Menu
{
private:
  vector<string> filenames;
  void readMenuCarregamento();
  int getFaseFromJson(string filename);

public:
  MenuCarregamento();
  ~MenuCarregamento();

  void desenhar();
  void executar();
  void Update(const char *teclaPressionada);
  string getSelectedSalve();
};
