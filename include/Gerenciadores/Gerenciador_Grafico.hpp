#ifndef GERENCIADOR_GRAFICO_HPP
#define GERENCIADOR_GRAFICO_HPP

// class Ente;
#include "Ente.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

class Ente;

class Gerenciador_Grafico
{
private:
  sf::RenderWindow window;

public:
  Gerenciador_Grafico();
  ~Gerenciador_Grafico();
  void desenharEnte(Ente *pE);
  void clear();
  void display();
  bool isWindowOpen();
  sf::Texture carregaTextura(string textura_path);
};

#endif // GERENCIADOR_GRAFICO_HPP