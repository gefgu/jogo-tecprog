#include "Gerenciadores/Gerenciador_Grafico.hpp"

Gerenciador_Grafico::Gerenciador_Grafico() : window(sf::VideoMode(800, 600), "Meu Jogo")
{
}

Gerenciador_Grafico::~Gerenciador_Grafico()
{
}

void Gerenciador_Grafico::desenharEnte(Ente *pE)
{
}

void Gerenciador_Grafico::display()
{
  sf::Event event;
  while (window.pollEvent(event))
  {
    if (event.type == sf::Event::Closed)
      window.close();
  }

  window.clear();
  window.display();
}

bool Gerenciador_Grafico::isWindowOpen()
{
  return window.isOpen();
}