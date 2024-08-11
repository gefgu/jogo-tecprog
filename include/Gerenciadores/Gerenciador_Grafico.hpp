#ifndef GERENCIADOR_GRAFICO_HPP
#define GERENCIADOR_GRAFICO_HPP

#include "Ente.hpp"
#include <SFML/Graphics.hpp>

class Gerenciador_Grafico
{
private:
  sf::RenderWindow window;

public:
  Gerenciador_Grafico();
  ~Gerenciador_Grafico();
  void desenharEnte(Ente *pE);
  void display();
  bool isWindowOpen();
};

#endif // GERENCIADOR_GRAFICO_HPP